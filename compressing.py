__author__ = 'anna'

import random
import string
import time
import argparse as asp

import compressor

MAX_LENGTH = 1000
MIN_LENGTH = 10

def string_generator():
    """
    Random string generator with lower case letters
    :return: generated string.
    :rtype: str
    """
    return ''.join(random.SystemRandom().choice(string.ascii_lowercase) for _ in range(random.randint(MIN_LENGTH, MAX_LENGTH)))

def setup_parser():
    """
    Configuring argparser.
    :return: argparser with all necessary parameters filled.
    :rtype: asp.ArgumentParser
    """
    parser = asp.ArgumentParser(
        'Searching max k-repeatings in strings',
        description='This program runs k-repeatings searching for string (or list with several strings). '
                    'The algorithm was written in C++.',
        epilog='This algorithm was proposed as task 1.4 in 2nd semester SHAD.')
    parser.add_argument('count', nargs='?', default=1, help='Quantity of strings', type=int)

    return parser

if __name__ == "__main__":
    args = setup_parser().parse_args()

    start = time.process_time()
    strings = [string_generator() for _ in range(args.count)] if args.strings is None else args.strings[:args.count]
    end = time.process_time()
    print("\tRetrieving string TIME: {:.5f} sec".format(end - start))

    start = time.process_time()
    results = compressor.count_rep_list(strings)
    [print('\nSTRING= ', s, '\nRESULT= ', res) for s, res in zip(strings, results)]
    end = time.process_time()
    print("\tProcessing algorithm TIME: {:.5f} sec".format(end - start))