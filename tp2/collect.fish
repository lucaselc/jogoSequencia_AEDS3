#!/usr/bin/env fish

set -l ranges_Dyn (seq 10000 2000 100000)
set -l ranges_Alt (seq 40)
set -l test_n 10

rm -r inputs

for x in $ranges_Dyn
    ./gen.py --num $x &
end

for x in $ranges_Alt
    ./gen.py --num $x &
end
wait

set -gx TP2_MACHINE 1
set -g db "times.db"

rm times.db

alias sqlite=sqlite3

sqlite $db "create table if not exists configuration(id string primary key, n int, strat string);"
sqlite $db "create table if not exists time(config_id int, user int, system int, clock int); --, foreign key(config_id) references time(id));"

function config -a n strat
    sqlite $db "select id from configuration where (n = $n) and (strat = '$strat')"
    sqlite $db "insert into configuration values('$n-$strat', $n, '$strat') returning id;"
end


function insert -a id user system clock
    sqlite $db "insert into time values('$id', $user, $system, $clock);"
end

for strat in Dyn Alt
    for x in $(eval echo \$ranges_$strat | string split ' ')
        echo Starting $strat $x

        set -l id (config $x $strat)

        for i in (seq $test_n)
            insert $id (./tp2 $strat inputs/entrada-$x.txt)
        end
    end
end
