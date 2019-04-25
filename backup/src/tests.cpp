ostringstream s1;
ostringstream s2;

// TEST 1 - Diff operator =
/*
s1 = ostringstream("");
s2 = ostringstream("");
Diff * d = new Diff(BinFile("file.txt"), BinFile("list.txt"));
s1 << *d;
Diff d2 = *d;
delete d;
s2 << d2;
assert(s1.str() == s2.str());
cout << "Test 1: OK" << endl;

// TEST 2 - BinFile operator =
s1 = ostringstream("");
s2 = ostringstream("");
BinFile * f1 = BinFile("my_file_1.txt").Clone();
BinFile * f2 = BinFile("my_file_2.txt").Clone();
s1 << *f1;
*f2 = BinFile(*f1);
delete f1;
s2 << *f2;
delete f2;
assert(s1.str() == s2.str());
cout << "Test 2: OK" << endl;
*/

BinFile * bf1 = new BinFile("data/file.txt");
BinFile * bf2 = new BinFile("data/list.txt");

Diff * d = new Diff(bf1, bf2);
cout << *d << endl;
Result<uint8_t> res = d->Compare();
res.Print(cout);

delete d;

/*
try
{
    d = new Diff();
    d->Compare();
    delete d;
}
catch(const char * e)
{
    std::cerr << e << '\n';
}
*/