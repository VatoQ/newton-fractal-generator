import csv
from PIL import Image

output_image = "fractal.png"

pixel_list:list[tuple[int, int, int]] = []
with open("image_data.csv", "r", newline="") as csv_file:
    reader = csv.reader(csv_file, delimiter=";")
    header = next(reader)


    X = int(header[-2])
    Y = int(header[-1])

    for row in reader:
        pixel_list.append((int(row[0]), int(row[1]), int(row[2])))


image = Image.new("RGB", (X, Y))

image.putdata(pixel_list)

image.save(output_image)
