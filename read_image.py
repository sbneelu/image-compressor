from PIL import Image
from sys import argv

_, input_file, output_file = argv

image = Image.open(input_file)

s = f"{image.width} {image.height}\n"

for i in range(image.width):
    for j in range(image.height):
        r, g, b = image.getpixel((i, j))
        s += f"{r} {g} {b} \n"

with open(output_file, 'w') as f:
    f.write(s)
