#!/bin/python3
""" Tool to plot chart from data generate by genetic algorithm """


import json
import argparse
from typing import Tuple, List
import matplotlib.pyplot as plt


def parse_data(path: str = '') -> Tuple[List[int], List[float], List[float]]:
    """
    Parses data from provided path
    :param path: Path to dataset.
    :return: Tuple of lists with: generations, average and maximum correctness in generation.
    """
    _generations = []
    _average_correctness = []
    _max_correctness = []
    with open(path, encoding="utf-8") as data_file:
        parsed_data = json.load(data_file)
        _generations = parsed_data["generations"]
        _average_correctness = parsed_data["averageCorrectness"]
        _max_correctness = parsed_data["maxCorrectness"]

    return _generations, _average_correctness, _max_correctness


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Chart plotter for genetic algorithm output')
    parser.add_argument('-f', '--file', dest='file')
    args = parser.parse_args()

    generations, average_correctness, max_correctness = parse_data(args.file)

    plt.figure()
    plt.plot(generations, average_correctness, label="Average correctness")
    plt.plot(generations, max_correctness, label="Maximum correctness")
    plt.xlabel("Generation")
    plt.ylabel("Correctness")
    plt.legend(loc="lower right")

    plt.savefig('plot.png')
    plt.show()
