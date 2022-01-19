import sys
import csv


def main():

    # Handle number of agruments in command line
    if len(sys.argv) != 3:
        print(f"Usage: python {sys.argv[0]} databases/'file'.csv sequences/'file'.txt")
        exit(1)

    csvfilename = sys.argv[1]
    seqfilename = sys.argv[2]

    # Read database into memory from file

    with open(csvfilename) as csvfile:
        reader = csv.DictReader(csvfile)
        dict_list = list(reader)

    # Read sequence file
    with open(seqfilename) as seqfile:
        sequence = seqfile.read()

    counts = []

    # write each 'name' of sequence into STR
    for i in range(1, len(reader.fieldnames)):
        STR = reader.fieldnames[i]
        counts.append(0)

        # loop for find STR in sequence file
        for j in range(len(sequence)):
            STR_count = 0

            # if STR its find in sequence, feed STR_count with number of repeat
            if sequence[j:(j + len(STR))] == STR:
                k = 0
                while sequence[(j + k):(j + k + len(STR))] == STR:
                    STR_count += 1
                    k += len(STR)
                if STR_count > counts[i - 1]:
                    counts[i - 1] = STR_count

    # check each list of dict to find match
    for i in range(len(dict_list)):
        matches = 0
        for j in range(1, len(reader.fieldnames)):
            # if match, feed matches and print matches
            if int(counts[j - 1]) == int(dict_list[i][reader.fieldnames[j]]):
                matches += 1
            if matches == (len(reader.fieldnames) - 1):
                print(dict_list[i]['name'])
                exit(0)

    print("No match")


main()