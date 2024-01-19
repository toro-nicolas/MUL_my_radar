import argparse
import random


class EntityGenerator:
    def __init__(self, planes, towers, delay, path):
        self.max_delay = delay
        self.planes = planes
        self.towers = towers
        self.tower_list = []
        self.path = path
        self.entities = []

    def generate_entities(self):
        for _ in range(self.towers):
            tower_x, tower_y = round(random.uniform(0, 1920), 10), round(random.uniform(0, 1080), 10)
            radius = round(random.uniform(0, 10), 10)
            self.tower_list.append([tower_x, tower_y, radius])
            entity = f"T  {tower_x} {tower_y}  {radius}"
            self.entities.append(entity)

        for _ in range(self.planes):
            index_tower = random.randint(0, len(self.tower_list))
            if len(self.tower_list) == 0:
                start_x = random.uniform(20, 1900)
                start_y = random.uniform(20, 1060)
            else:
                start_x = self.tower_list[index_tower - 1][0]
                start_y = self.tower_list[index_tower - 1][1]
            if len(self.tower_list) <= 1:
                end_x = random.uniform(20, 1900)
                end_y = random.uniform(20, 1060)
            else:
                index_end_tower = random.randint(0, len(self.tower_list))
                while index_tower == index_end_tower:
                    index_end_tower = random.randint(0, len(self.tower_list))
                end_x = self.tower_list[index_end_tower - 1][0]
                end_y = self.tower_list[index_end_tower - 1][1]
            speed = round(random.uniform(1, 5), 10)
            delay = round(random.uniform(0, self.max_delay), 10)
            entity = f"A  {start_x} {start_y}  {end_x} {end_y}  {speed}  {delay}"
            self.entities.append(entity)

    def save_entities(self):
        with open(self.path, 'w') as file:
            file.write('\n'.join(self.entities))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('-p', '--planes', metavar="Planes", required=True, type=int, help="Number of planes")
    parser.add_argument('-t', '--towers', metavar="Towers", required=True, type=int, help="Number of towers")
    parser.add_argument('-d', '--delay', metavar="Delay", required=True, type=int, help="Maximum delay")
    parser.add_argument('-pa', '--path', metavar="Path", required=True, type=str, help="Path to the output file")
    args = parser.parse_args()

    generator = EntityGenerator(args.planes, args.towers, args.delay, args.path)
    generator.generate_entities()
    generator.save_entities()
