/^debugfs [1-9]\.[0-9]*[.-][^ ]* ([0-9]*-[A-Za-z]*-[0-9]*)/d
/^dumpe2fs [1-9]\.[0-9]*[.-][^ ]* ([0-9]*-[A-Za-z]*-[0-9]*)/d
/^e2fsck [1-9]\.[0-9]*[.-][^ ]* ([0-9]*-[A-Za-z]*-[0-9]*)/d
/^mke2fs [1-9]\.[0-9]*[.-][^ ]* ([0-9]*-[A-Za-z]*-[0-9]*)/d
/^resize2fs [1-9]\.[0-9]*[.-][^ ]* ([0-9]*-[A-Za-z]*-[0-9]*)/d
/^tune2fs [1-9]\.[0-9]*[.-][^ ]* ([0-9]*-[A-Za-z]*-[0-9]*)/d
s/\\015//g
/automatically checked/d
/^Directory Hash Seed:/d
/Discarding device blocks/d
/^Filesystem created:/d
/^Filesystem flags:/d
/^Filesystem UUID:/d
/^JFS DEBUG:/d
/^Last write time:/d
/^Last mount time:/d
/^Last checked:/d
/^Lifetime writes:/d
/^Maximum mount count:/d
/^Next check after:/d
/^Suggestion:/d
/Reserved blocks uid:/s/ (user .*)//
/Reserved blocks gid:/s/ (group .*)//
/whichever comes first/d
/^  Checksum /d
