import os
from datalink import SenderDataLink, RecieverDataLink
import pytest

INFILE   =  "datalink/tests/data/input.txt"
TEMPFILE =  "datalink/tests/data/framed.bin"
OUTFILE  =  "datalink/tests/data/output.txt"

@pytest.mark.parametrize("inp, expected", [
    ("this is the $string", [b"#this is #", b"#the $$str#", b"#ing#"])
])
def test_senter_framing(inp, expected):
    with open("temp.txt", "w") as tmp:
        tmp.write(inp)
    sender = SenderDataLink("temp.txt", frame_size=8)
    assert sender.num_frames     == len(expected)
    assert sender.stuffed_frames == expected
    os.remove("temp.txt")

@pytest.mark.parametrize("inp, expected", [
    (b"#this is ##the $$str##ing#", [b"this is ", b"the $str", b"ing"])
])
def test_reciever_framing(inp, expected):
    with open("temp.txt", "wb") as tmp:
        tmp.write(inp)
    reciever = RecieverDataLink("temp.txt")
    assert reciever.num_frames     == len(expected)
    assert reciever.frames         == expected
    os.remove("temp.txt")

def test_sender_reciver():
    sender = SenderDataLink(infile=INFILE, outfile=TEMPFILE, frame_size=8)
    sender.dump()

    reciever = RecieverDataLink(infile=TEMPFILE, outfile=OUTFILE)
    reciever.dump()

    with open(INFILE, "r") as f:
        sent = f.read()
    with open(OUTFILE, "r") as f:
        recieved = f.read()

    assert sender.num_frames == reciever.num_frames
    assert sent == recieved
