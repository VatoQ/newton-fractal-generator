import csv
from PIL import Image

print("Enter make_png.py")
output_image = "fractal.png"

print("\tRead data from csv...")
pixel_list:list[tuple[int, int, int]] = []
with open("image_data.csv", "r", newline="") as csv_file:
    reader = csv.reader(csv_file, delimiter=";")
    header = next(reader)


    X = int(header[-2])
    Y = int(header[-1])

    for row in reader:
        pixel_list.append((int(row[0]), int(row[1]), int(row[2])))

print("\tMake new image...")

image = Image.new("RGB", (X, Y))


image.putdata(pixel_list)

print("\tSave image...")
image.save(output_image)
print("Exit make_png")
