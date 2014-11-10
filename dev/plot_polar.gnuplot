reset

set terminal png size 480,250
set output 'plot_polar.png'

unset key
set polar
set angles degrees

set grid polar 30

unset xtics
unset ytics
set rtics ("" 0, "" 1, "" 2, "" 3)

set rrange [0: 3]
set trange [-180: 180]

set linestyle 1 linewidth 2
set linestyle 2 linewidth 2
set linestyle 3 linewidth 2
set xrange [-1: 3]
set yrange [-2: 2]
plot cos(t)-1 with lines linetype 1, 1.1*(cos(t)-1) with lines linetype 2, 1.2*(cos(t)-1) with lines linetype 3

