import time
import sys
import os
import copy

live_cell, dead_cell = "*", " "


def game_of_life():
    cycles = int(input("Enter number of cycles: "))
    os.system('cls' if os.name == 'nt' else 'clear')
    game_table = list()
    with open(sys.argv[1], "r") as f:
        for line in f.readlines():
            new_row = []
            new_row.extend(line)
            new_row.pop()
            game_table.append(new_row)
    _display_table(game_table)
    for cycle in range(cycles):
        time.sleep(1)
        os.system('cls' if os.name == 'nt' else 'clear')
        new_game_table = _calculate_new_game_table(game_table)
        _display_table(new_game_table)
        game_table = new_game_table


def _display_table(game_table):
    print("_" * len(game_table[0]))
    for row in game_table:
        for cell in row:
            print(cell, end="")
        print("|")
    print("-" * len(game_table[0]) + "|")


def _calculate_new_game_table(game_table):
    new_game_table = copy.deepcopy(game_table)
    for index_row, row in enumerate(iter(game_table)):
        for index_column, cell in enumerate(iter(row)):
            new_cell_value = _get_cell_value(
                game_table, index_row, index_column)
            new_game_table[index_row][index_column] = new_cell_value
    return new_game_table


def _get_cell_value(game_table, index_row, index_column):
    adjacent_cells_values = list()
    for column in range(index_column - 1, index_column + 2):
        for row in range(index_row - 1, index_row + 2):
            if (row, column) == (index_row, index_column):
                continue
            # print(row, column)
            try:
                if row >= 0 and column >= 0:
                    adjacent_cells_values.append(game_table[row][column])
            except:
                pass
    live_neighbours = adjacent_cells_values.count(live_cell)

    if game_table[index_row][index_column] == live_cell:
        if live_neighbours < 2:
            return dead_cell
        elif live_neighbours in (2, 3):
            return live_cell
        elif live_neighbours > 3:
            return dead_cell
    elif game_table[index_row][index_column] == dead_cell:
        if live_neighbours == 3:
            return live_cell
        else:
            return dead_cell





if __name__ == "__main__":
    game_of_life()
