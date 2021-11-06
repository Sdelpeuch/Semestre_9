from matplotlib import pyplot as plt


def plot_map():
    with open('map.txt') as f:
        for line in f:
            x, y = line.split(',')
            plt.plot(float(x), float(y), 'bo')
    plt.savefig('map.png')
    plt.show()


if __name__ == "__main__":
    plot_map()
