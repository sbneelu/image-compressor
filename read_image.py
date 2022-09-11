from PIL import Image
from sys import argv

_, input_file, output_file = argv

image = Image.open(input_file)

s = f"{image.width}\n{image.height}\n"

for i in range(image.size[0]):
    for j in range(image.size[1]):
        s += " ".join(str(c) for c in image.getpixel((i, j))) + "\n"

with open(output_file, 'w') as f:
    f.write(s)
