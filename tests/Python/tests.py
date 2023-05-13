#! /usr/bin/env python3

import mt19937


def tests():
    """Test MT19937 in Python."""
    for _ in range(9999):
        mt19937.rand32()
        mt19937.rand64()

    assert mt19937.rand32() == 0xF5CA0EDB
    assert mt19937.rand64() == 0x8A8592F5817ED872


def main():
    """Main function."""
    tests()


if __name__ == '__main__':
    main()
