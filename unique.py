#!/usr/bin/env python3

import os
import sys

# Functions

def usage(status=0):
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [flags]
    -c      Prefix lines by the number of occurrences
    -d      Only print duplicate lines
    -i      Ignore differences in case when comparing, prints out full line in lowercase
    -u      Only print unique lines
By default, {progname} prints one of each type of line.''')
    sys.exit(status)

def count_frequencies(stream=sys.stdin, ignore_case=False):
    
    frequencies = {}
    for line in stream:
        line = line.rstrip()
        
        if ignore_case:
            line = line.lower()

        if line in frequencies:
            frequencies[line] += 1
        else:
            frequencies[line] = 1
    
    return frequencies      

def print_lines(frequencies, occurrences=False, duplicates=False, unique_only=False):

    for key, value in frequencies.items():
        if occurrences:
            if duplicates:
                if value > 1:
                    print(f'{value:>7} {key}')
            elif unique_only:
                if value == 1:
                    print(f'{value:>7} {key}')
            else:
                print(f'{value:>7} {key}')
        else:
            if duplicates:
                if value > 1:
                    print(key)
            elif unique_only:
                if value == 1:
                    print(key)  
            else:
                print(key)
        
def main():
    
    case_sensitive = False
    show_count = False
    show_duplicates = False
    show_unique = False

    good_flags = ["-h", "-i", "-c", "-d", "-u"]

    for arg in sys.argv[1:]:
        if arg == "-h":
            usage()
        if arg == "-i":
            case_sensitive = True;
        if arg == "-c":
            show_count = True
        if arg == "-d":
            show_duplicates = True
        if arg == "-u":
            show_unique = True
        if arg not in good_flags:
            usage()
        
    frequencies = count_frequencies(ignore_case=case_sensitive)
    print_lines(frequencies, show_count, show_duplicates, show_unique);

# Main Execution

if __name__ == '__main__':
    main()
