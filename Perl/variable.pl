$meal = "brontosaurus steak";
$barney = "fred ate a $meal\n";
print $barney;
$barney = 'fred ate a '.$meal."\n";
print $barney;

print "------------------\n";

$what = "brontosaurus steak";
$n = 3;
print "fred ate $n $whats.\n";
print "fred ate $n ${what}s.\n";
print "fred ate $n $what"."s.\n";
print 'fred ate '.$n.' '.$what."s.\n";

print "------------------\n";

$alef = chr(0x05D0);
$alpha = chr(hex('03B1'));
$omega = chr(0x03C9);

print $alef;