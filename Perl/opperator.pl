$name = 'issac';
if ($name gt "fred") {
    print "'$name' next to 'fred'\n";
}

$line = <STDIN>;
if ($line eq "\n") {
    print "Nothing.";
} else {
    print "Line : $line";
}

$text = chomp($in = <STDIN>);
print $text;
print $in;