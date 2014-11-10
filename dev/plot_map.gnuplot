reset

set terminal png size 480,250
set output 'plot_map.png'

unset key
set grid
set format ''
set linestyle 1 linewidth 2
set linestyle 2 linewidth 0.5 linecolor rgb "black"
plot 'world.dat' with lines linestyle 2, 'plot_map.dat' with lines linestyle 1
