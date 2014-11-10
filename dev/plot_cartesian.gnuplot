reset

set terminal png size 480,250
set output 'plot_cartesian.png'

unset key
set grid 
set xrange [0:8]

set xtics ("" 0, "" 1, "" 2, "" 3, "" 4, "" 5, "" 6, "" 7, "" 8)
set ytics ("" 0, "" 2, "" 4, "" 6, "" 8, "" 8, "" 10, "" 12)

set linestyle 1 linewidth 2
set linestyle 2 linewidth 2
set linestyle 3 linewidth 2
plot x+sin(x) with lines linetype 1, 1+x+sin(x) with lines linetype 2, 2+x+sin(x) with lines linetype 3
