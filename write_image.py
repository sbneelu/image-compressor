from PIL import Image

with open('image.txt', 'r') as f:
    lines = f.readlines()

width = int(lines[0])
height = int(lines[1])

image = Image.new('RGB', (width, height))

for i in range(width):
    for j in range(height):
        image.putpixel(
            (i, j),
            tuple(int(c) for c in lines[i * width + j + 2].split())
        )

image.save('new_image.jpg')
