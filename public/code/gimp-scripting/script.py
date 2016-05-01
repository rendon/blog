import os, re
from gimpfu import *

for file in os.listdir(os.getcwd()):
    if not re.search('jpeg', file):
        continue

    image = pdb.gimp_file_load(file, '1') # Open file
    pdb.gimp_image_scale(image, 150, 150) # and scale

    # Apply round corners filter
    drawable = pdb.gimp_image_active_drawable(image)
    pdb.script_fu_round_corners(image, drawable, 9, 1, 8, 8, 9, 0, 0)
    image.merge_visible_layers(0)
    drawable = pdb.gimp_image_active_drawable(image)

    # Save file with PNG format
    temp = file.split('.')
    temp.pop()
    output_file = temp.pop() + ".png"
    pdb.gimp_file_save(image, drawable, output_file, 'Saved file')
