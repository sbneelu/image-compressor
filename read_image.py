from PIL import Image

image = Image.open('pfp.jpg')

s = f"{image.width}\n{image.height}\n"

for i in range(image.size[0]):
    for j in range(image.size[1]):
        s += " ".join(str(c) for c in image.getpixel((i, j))) + "\n"

with open('image.txt', 'w') as f:
    f.write(s)
