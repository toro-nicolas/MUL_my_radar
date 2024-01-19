import argparse
from random import randint


class EntityGenerator:
    def __init__(self, planes, towers, path):
        self.planes = planes
        self.towers = towers
        self.path = path
        self.entities = []

    def generate_entities(self):
        for _ in range(self.planes):
            start_x, start_y = randint(20, 1900), randint(20, 1060)
            end_x, end_y = randint(20, 1900), randint(20, 1060)
            speed = randint(1, 5)
            delay = randint(0, 60)
            entity = (f"A  {start_x} {start_y}  {end_x} {end_y}  {speed}  {delay}")
            self.entities.append(entity)

        for _ in range(self.towers):
            tower_x, tower_y = randint(200, 1920), randint(200, 1080)
            radius = randint(1, 50)#100)
            entity = f"T  {tower_x} {tower_y}  {radius}"
            self.entities.append(entity)

    def save_entities(self):
        with open(self.path, 'w') as file:
            file.write('\n'.join(self.entities))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--planes', metavar="Planes", required=True, type=int, help="Number of planes")
    parser.add_argument('-t', '--towers', metavar="Towers", required=True, type=int, help="Number of towers")
    parser.add_argument('-pa', '--path', metavar="Path", required=True, type=str, help="Path to the output file")
    args = parser.parse_args()

    generator = EntityGenerator(args.planes, args.towers, args.path)
    generator.generate_entities()
    generator.save_entities()
