int main(int argc, char *argv[])
{
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        exit(1);
    }

    string action(argv[1]);
    if (action != "encode" && action != "decode") {
        cerr << "Not a valid action: " << action << endl;
        exit(1);
    }

    string ifname(argv[2]);
    ifstream infile(ifname);
    if (!infile.is_open()) {
        cerr << "Couldn't open input file: " << ifname << endl;
        exit(1);
    }

    string ofname(argv[3]);
    ofstream outfile(ofname);
    if (!outfile.is_open()) {
        cerr << "Couldn't open output file: " << ofname << endl;
        exit(1);
    }

    if (action == "encode") {
        cout << "Encoding file " << ifname << "..." << endl;
        encode(infile, outfile);
    } else {
        cout << "Decoding file " << ifname << "..." << endl;
        decode(infile, outfile);
    }

    infile.close();
    outfile.close();
    return 0;
}
