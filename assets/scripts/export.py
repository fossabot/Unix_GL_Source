import sys, os
sys.path.append("/usr/local/lib/python2.7/site-packages")
from PIL import Image, ImageOps
from images2gif import writeGif

def makeAnimMovie(imagefilepath, numImages):
    if(type(imagefilepath) != type("")):
        print "GIF::EXPORTER:: 1st arg is not a string, make it a string.\n"
        return

    if(type(numImages) != type(1)):
        print "GIF::EXPORTER:: 2nd arg is not an integer, make it an integer.\n"
        return

    # FLIPPING IMAGES BACK TO NORMAL
    file_head = imagefilepath[:-4]
    file_tail = imagefilepath[-4:]
    gif_images_buffer = []
    gif_images_size = 0
    for i in range(1, numImages + 1):
        red = ""
        if(i < 10):
            red = "000" + str(i)
        elif(i < 100):
            red = "00" + str(i)
        elif(i < 1000):
            red = "0" + str(i)
        im = Image.open(file_head + red + file_tail)
        pix = im.load()
        gif_images_size = im.size
        flipped_im = im.transpose(Image.FLIP_TOP_BOTTOM)
        flipped_path = file_head + "_" + red + file_tail
        flipped_im.save(flipped_path)
        gif_images_buffer.append(flipped_path)
        os.remove(file_head + red + file_tail)
    # END FLIPPING

    for gif in gif_images_buffer:
        print gif

    # MAKING GIF
    m_images = [Image.open(fn) for fn in gif_images_buffer]
    writeGif("../exports/anim.gif", m_images, duration=0.2)
    # END MAKING


if __name__ == '__main__':
    try:
        makeAnimMovie(sys.argv[1], int(sys.argv[2]))
    except:
        pass

    try:
        os.system("make movie")
    except:
        pass
