from PIL import Image
from sys import argv

_, input_file, output_file = argv

with open(input_file, 'r') as f:
    lines = f.readlines()

width, height = map(int, lines[0].split())

image = Image.new('RGB', (width, height))

pixels = lines[1:]
for i in range(width):
    for j in range(height):
        pixel = pixels[i * height + j]
        r, g, b = map(int, pixel.split())
        image.putpixel((i, j), (r, g, b))

image.save(output_file)
