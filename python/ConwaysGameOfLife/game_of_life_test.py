import unittest
import game_of_life as got

class TestGameOfLife(unittest.TestCase):

    def setUp(self):
        self.game_table = list()
        with open("board_test_oscillator.txt", "r") as f:
            for line in f.readlines():
                new_row = []
                new_row.extend(line)
                new_row.pop()
                self.game_table.append(new_row)

    def test_get_cell_value(self):
        expected_values = [[' ', ' ', ' ', ' ', ' '],
                           [' ', ' ', ' ', ' ', ' '],
                           [' ', '*', '*', '*', ' '],
                           [' ', ' ', ' ', ' ', ' '],
                           [' ', ' ', ' ', ' ', ' ']]
        for i in range(0, 5):
            for j in range(0, 5):
                self.assertEqual(
                    got._get_cell_value(self.game_table, i, j), expected_values[i][j])

    def test_calculate_new_game_table(self):
        print(self.game_table)
        new_game_table = got._calculate_new_game_table(self.game_table)
        print(new_game_table)
        expected_values = [[' ', ' ', ' ', ' ', ' '],
                           [' ', ' ', ' ', ' ', ' '],
                           [' ', '*', '*', '*', ' '],
                           [' ', ' ', ' ', ' ', ' '], 
                           [' ', ' ', ' ', ' ', ' ']]
        self.assertEqual(new_game_table, expected_values)

if __name__ == '__main__':
    unittest.main()
