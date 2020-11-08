import os

class BaseDataLink:
    FLAG            = b"#"
    ESC             = b"$"
    MAX_FRAME_SIZE  = 1024
    BIT_PATTERN     = "01111110"
    FRAMING_METHODS = {"byte", "bit"}


class SenderDataLink(BaseDataLink):
    """Sender Datalink Layer."""

    def __init__(self, infile: str, outfile="output.bin", framing_method="byte", frame_size=256):
        self._assert_all_valid(infile, outfile, framing_method, frame_size)

        self.infile          = infile
        self.outfile         = outfile
        self.framing_method  = framing_method
        self.frame_size      = frame_size

        # Lazy Execution
        self._frames         = None
        self._num_frames     = None
        self._stuffed_frames = None

    @property
    def frames(self) -> list:
        """A list of frames to be sent by the sender."""
        # If not present, fetch the frames
        if self._frames is None:
            self._frames = self.get_frames()
        # Monkey patch if already present
        return self._frames

    @property
    def num_frames(self) -> int:
        """The number of frames sent by the sender."""
        return len(self.frames)

    def _assert_all_valid(self, infile, outfile, framing_method, frame_size):
        assert isinstance(infile, str) and os.path.isfile(infile), \
               "'infile' must be a valid file (path to the input file)."
        assert isinstance(outfile, str) and os.path.isfile(infile), \
               "'outfile' must be a valid file (path to the output file)."
        assert isinstance(framing_method, str) and framing_method in self.FRAMING_METHODS, \
               f"'framing_method' must be a string from the set {self.FRAMING_METHODS}."
        assert isinstance(frame_size, int) and frame_size <= self.MAX_FRAME_SIZE and frame_size>=1, \
               f"'frame_size' must be a integer less than {self.MAX_FRAME_SIZE} and greater than 0."

    def get_frames(self) -> list:
        """Get the frames to be sent by the sender. Also accessible by the property '.frames'"""
        frames = []

        with open(self.infile, "rb") as f:
            frame = f.read(self.frame_size)
            while frame:
                frames.append(frame)
                frame = f.read(self.frame_size)

        return frames

    def _stuff_bits(self):
        """Bit stuffing algorithm."""
        import re
        from binascii import hexlify

        def _convert_to_bin(frame):
            return bin(int(hexlify(frame), base=16))[2:]

        bit_frames = list(map(_convert_to_bin, self.frames))

        def _stuffer(frame):
            return self.BIT_PATTERN + re.sub("11111", "111110", frame) + self.BIT_PATTERN

        stuffed_frames = list(map(_stuffer, bit_frames))

        def _string_to_bytes(s):
            b = bytearray()
            b.extend(map(ord, s))
            return b

        stuffed_frames = list(map(_string_to_bytes, stuffed_frames))

        return stuffed_frames

    def _stuff_bytes(self) -> list:
        """Byte stuffing algorithm"""
        import re

        # A function that stuffs a single frame
        def _stuffer(frame: bytes) -> list:
            frame = re.sub(b"\\" + self.ESC, self.ESC + self.ESC, frame)
            frame = re.sub(b"\\" + self.FLAG, self.ESC + self.FLAG, frame)
            frame = self.FLAG + frame + self.FLAG
            return frame

        return list(map(_stuffer, self.frames))

    def stuff(self) -> list:
        """
        Stuffs frames to be transmitted using the framing method
        specified during instantiation.
        """
        methname = "_stuff_" + self.framing_method + "s"
        methobj = getattr(self, methname, self._stuff_bytes)
        return methobj()

    @property
    def stuffed_frames(self) -> list:
        """A list of stuffed frames to be transmitted directly to the reciever."""
        # If not present, fetch the stuffed frames
        if self._stuffed_frames is None:
            self._stuffed_frames = self.stuff()
        # Monkey patch if already present
        return self._stuffed_frames

    def dump(self):
        """
        Save the frames to be transmitted in a file that will be
        accessed by the reciever.
        """
        with open(self.outfile, "wb") as f:
            for frame in self.stuffed_frames:
                f.write(frame)


class RecieverDataLink(BaseDataLink):
    """Reciever Datalink layer."""
    def __init__(self, infile: str, outfile="output.txt", framing_method="byte"):
        self._assert_all_valid(infile, outfile, framing_method)

        self.infile          = infile
        self.outfile         = outfile
        self.framing_method  = framing_method

        # Lazy Execution
        self._frames         = None
        self._num_frames     = None

    @property
    def frames(self) -> list:
        """A list of frames recieved from the sender."""
        # If not present, fetch the frames
        if self._frames is None:
            self._frames = self.get_frames()
        # Monkey patch if already present
        return self._frames

    @property
    def num_frames(self) -> int:
        """The number of frames recieved from the sender"""
        return len(self.frames)

    def _assert_all_valid(self, infile, outfile, framing_method):
        assert isinstance(infile, str) and os.path.isfile(infile), \
               "'infile' must be a valid file (path to the input file)."
        assert isinstance(outfile, str) and os.path.isfile(infile), \
               "'outfile' must be a valid file (path to the output file)."
        assert isinstance(framing_method, str) and framing_method in self.FRAMING_METHODS, \
               f"'framing_method' must be a string from the set {self.FRAMING_METHODS}."

    def _get_bit_frames(self) -> list:
        """Get the data out of bit frames."""
        import re

        with open(self.infile, "r") as f:
            buffer = f.read()

        striped_buffer = buffer[len(self.BIT_PATTERN):-(len(self.BIT_PATTERN))]
        stuffed_frames = striped_buffer.split(self.BIT_PATTERN + self.BIT_PATTERN)

        frames = []

        for stuffed_frame in stuffed_frames:
            frames.append(re.sub("111110", "11111", stuffed_frame))

        def _bitstring_to_bytes(s):
            return int(s, 2).to_bytes((len(s) + 7) // 8, "big")

        frames = list(map(_bitstring_to_bytes, frames))

        return frames

    def _get_byte_frames(self) -> list:
        """Get the data out of byte frames."""
        with open(self.infile, "rb") as f:
            buffer = f.read()

        frame = b""
        frames = []
        i = 1

        while i < len(buffer):
            byte = buffer[i].to_bytes(1, "big")

            if byte == self.FLAG:
                frames.append(frame)
                frame = b""
                i+=2
            elif byte == self.ESC:
                frame += buffer[i+1].to_bytes(1, "big")
                i+=2
            else:
                frame += byte
                i+=1

        return frames

    def get_frames(self) -> list:
        """Get the frames recieved from the sender."""
        methname = "_get_" + self.framing_method + "_frames"
        methobj = getattr(self, methname, self._get_byte_frames)
        return methobj()

    def dump(self):
        """Save the data recieved in a file specified during instantiation."""
        with open(self.outfile, "wb") as f:
            for frame in self.frames:
                f.write(frame)
