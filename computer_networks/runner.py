import argparse
from datalink import SenderDataLink, RecieverDataLink

DESCRIPTION = """
Run practical 3 on your machine.
"""

USAGE = """runner.py [-h] --infile infile [--outfile outfile] [--tempfile tempfile] [--frame_size frame_size] [--framing_method framing_method]

Run practical 3 on your machine.

For example, you can pass the following parameters:

python runner.py --infile="data/input.txt" --outfile "data/output.txt" --tempfile "data/tempfile.bin" --frame_size 8 --framing_method "byte"

This will run the practical 3 with arguments "infile" (where the data is present), "outfile" (where to put the data),
"tempfile" (Temporary file where to put the temporary framed binary data), "frame_size" (size of each frame in bytes),
and "framing_method" (stuffing method. can be "bit" for bit stuffing and "byte" for byte stuffing).

"""

parser = argparse.ArgumentParser(description=DESCRIPTION, usage=USAGE)

parser.add_argument('--infile', metavar='infile', type=str, action='store',
                    help='Input file where data to be sent is present',
                    required=True)
parser.add_argument('--outfile', metavar='outfile', type=str, action='store',
                    help='Output file where data to be recieved should be put',
                    default="output.txt")
parser.add_argument('--tempfile', metavar='tempfile', type=str, action='store',
                    help='Temporary file where to put the temporary framed binary data',
                    default="temp.bin")
parser.add_argument('--frame_size', metavar='frame_size', type=int, action='store',
                    help='Size of each frame in bytes.',
                    default=8)
parser.add_argument('--framing_method', metavar='framing_method', type=str, action='store',
                    help='Framing Method. Can be "bit" for bit stuffing and "byte" for byte stuffing',
                    default="byte")
parser.add_argument('-v', '--verbose', action='store_true',
                    help='Print all the frames and stuffed frames')


if __name__ == "__main__":
    kwargs = vars(parser.parse_args())
    print()
    sender = SenderDataLink(infile=kwargs["infile"],
                            outfile=kwargs["tempfile"],
                            framing_method=kwargs["framing_method"],
                            frame_size=kwargs["frame_size"])
    sender.dump()

    # Print the sent frames if verbosity is true.
    if kwargs["verbose"]:
        print("Frames sent by the sender : ")
        for i, frame in enumerate(sender.frames):
            print(f"Frame {i+1} : {frame}")
        print()

    # Create the reciever
    reciever = RecieverDataLink(infile=kwargs["tempfile"],
                                outfile=kwargs["outfile"],
                                framing_method=kwargs["framing_method"])
    reciever.dump()

    # Print the recieved frames if verbosity is true.
    if kwargs["verbose"]:
        print("Frames recieved by the reciever : ")
        for i, frame in enumerate(reciever.frames):
            print(f"Frame {i+1} : {frame}")
        print()
    print("Executed Successfully! Please check the results in their respective files.")
    print()
