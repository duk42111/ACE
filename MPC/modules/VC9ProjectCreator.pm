package VC9ProjectCreator;

# ************************************************************
# Description   : A VC9 Project Creator
# Author        : Johnny Willemsen
# Create Date   : 11/22/2007
# $Id: VC9ProjectCreator.pm 2035 2011-10-06 15:05:21Z johnnyw $
# ************************************************************

# ************************************************************
# Pragmas
# ************************************************************

use strict;

use VC8ProjectCreator;

use vars qw(@ISA);
@ISA = qw(VC8ProjectCreator);

my %config = ('vcversion' => '9.00',
              'prversion' => '9.0.30729',
              'toolsversion' => '3.5',
              'targetframeworkversion' => '3.5',
              'xmlheader' => 1,
              );

# ************************************************************
# Subroutine Section
# ************************************************************

sub get_configurable {
  my($self, $name) = @_;
  return $config{$name};
}

1;
