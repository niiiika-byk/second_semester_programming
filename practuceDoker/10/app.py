with open("/home/filedir/text.txt") as file_handler:
    for line in file_handler:
        with open("/home/otherfiledir/text.txt", 'a') as otherfile_handler:
            otherfile_handler.write(line)
