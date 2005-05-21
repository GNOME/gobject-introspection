#! /usr/bin/perl -w

use Getopt::Long;
use XML::Parser;

my $INCLUDES;
my $PRINT_VERSION;
my $PRINT_HELP;

%optctl = (includes => \$INCLUDES);
	   
GetOptions(\%optctl, "includes=s");

my $file = shift;

die "Can't find file \"$file\""
  unless -f $file;
    
my $parser = new XML::Parser(ErrorContext => 2);

my $structname = "";
my $classname = "";

open OUTPUT, ">dump-sizes.c" || die "Cannot open dump-sizes.c: $!\n";

print OUTPUT <<EOT;
#include <glib.h>
$INCLUDES

int
main (int argc, char *argv[])
{
EOT

$parser->setHandlers(Start => \&start_handler,
		     End => \&end_handler);

$parser->parsefile($file);

print OUTPUT <<EOT;

  return 0;
}
EOT

close OUTPUT;

$CC = $ENV{CC} ? $ENV{CC} : "gcc";
$LD = $ENV{LD} ? $ENV{LD} : $CC;
$CFLAGS = $ENV{CFLAGS} ? $ENV{CFLAGS} : "";
$LDFLAGS = $ENV{LDFLAGS} ? $ENV{LDFLAGS} : "";

my $o_file;
if ($CC =~ /libtool/) {
  $o_file  = "dump-sizes.lo"
} else {
  $o_file = "dump-sizes.o"
}

$command = "$CC $CFLAGS -c -o $o_file dump-sizes.c && $LD -o dump-sizes $o_file $LDFLAGS";

system($command) == 0 or die "Compilation failed\n";

system("./dump-sizes > sizes.out") == 0 or die "Scan failed\n";

#unlink "./dump-sizes.c", "./dump-sizes.o", "./dump-sizes.lo", "./dump-sizes";

my %Sizes;

open SIZES, "<sizes.out" || die "Can't open sizes.out: $!";
while (<SIZES>) {
  if (m/(\w*) (\w*) (\d*)/) {
    $Sizes{$1 . "." . $2} = $3;
  }
}

close SIZES;

open OUTPUT2, ">$file.new" || die "Cannot open $file.new: $!\n";

$parser->setHandlers(Start => \&dump_start_handler,
		     End => \&dump_end_handler);

$parser->parsefile($file);

close OUTPUT2;

sub start_handler
{
    my $p = shift;
    my $el = shift;
    my $name = "";
    my $cname = "";
    my $class = "";

    while (@_) {
	my $att = shift;
	my $val = shift;

	if ($att eq "name") {
	    $name = $val;
	}
	elsif ($att eq "cname") {
	    $cname = $val;
	}
	elsif ($att eq "class") {
	    $class = $val;
	}
    }

    if (($el eq "object") || ($el eq "interface")) {
	if (!($cname eq "")) {
	    $structname = $cname;
	}
	else {
	    $structname = $name;
	}

	if (!($class eq "")) {
	    $classname = $class;
	}
	elsif ($el eq "object") {
	    $classname = $structname . "Class";
	}
	else {
	    $classname = $structname . "Iface";
	}
    }
    elsif ($el eq "field") {
	if (!($cname eq "")) {
	    need_offset ($structname, $cname);
	}
	else {
	    need_offset ($structname, $name);
	}
    }
    elsif ($el eq "vfunc") {
	if (!($cname eq "")) {
	    need_offset ($classname, $cname);
	}
	else {
	    need_offset ($classname, $name);
	}
    }
}

sub end_handler
{
    my $p = shift;
    my $el = shift;
    
    if (($el eq "object") || 
	($el eq "interface") ||
	($el eq "boxed") ||
	($el eq "struct") ||
	($el eq "union")) {
	$structname = "";
	$classname = "";
    }
}

sub need_offset
{
    my $struct = shift;
    my $name = shift;

    print OUTPUT "  g_print (\"$struct $name %d\\n\", G_STRUCT_OFFSET ($struct, $name));\n";
}

sub write_offset
{
    my $struct = shift;
    my $name = shift;

    print OUTPUT2 " offset=\"" . $Sizes{$struct . "." . $name } . "\""
}

sub dump_start_handler
{
    my $p = shift;
    my $el = shift;
    my $name = "";
    my $cname = "";
    my $class = "";

    print OUTPUT2 "<$el";

    while (@_) {
	my $att = shift;
	my $val = shift;

	print OUTPUT2 " $att=\"$val\"";

	if ($att eq "name") {
	    $name = $val;
	}
	elsif ($att eq "cname") {
	    $cname = $val;
	}
	elsif ($att eq "class") {
	    $class = $val;
	}
    }

    if (($el eq "object") || ($el eq "interface")) {
	if (!($cname eq "")) {
	    $structname = $cname;
	}
	else {
	    $structname = $name;
	}

	if (!($class eq "")) {
	    $classname = $class;
	}
	elsif ($el eq "object") {
	    $classname = $structname . "Class";
	}
	else {
	    $classname = $structname . "Iface";
	}
    }
    elsif ($el eq "field") {
	if (!($cname eq "")) {
	  write_offset ($structname, $cname);
	}
	else {
	  write_offset ($structname, $name);
	}
    }
    elsif ($el eq "vfunc") {
      if (!($cname eq "")) {
	write_offset ($classname, $cname);
      }
      else {
	write_offset ($classname, $name);
      }
    }
    print OUTPUT2 ">\n";
}

sub dump_end_handler
{
    my $p = shift;
    my $el = shift;
    
    if (($el eq "object") ||
	($el eq "interface") ||
	($el eq "boxed") ||
	($el eq "struct") ||
	($el eq "union")) {
	$structname = "";
	$classname = "";
    }

    print OUTPUT2 "</$el>\n";
}

