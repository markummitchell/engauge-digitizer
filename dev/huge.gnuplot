set grid
set xrange [0: 10]
set yrange [-10: 6]
set xtics font ", 30" offset 0,-0.5
set ytics font ", 30"
set key font ", 30"
set key spacing 2
set grid xtics lt 1 lw 2 lc rgb "gray"
set grid ytics lt 1 lw 2 lc rgb "gray"

set term png size 4000,2000
set output "huge.png"
plot 2*log(x/2)+1 with lines lw 2 lc rgb "red", 3*log(x/3)+2 with lines lw 2 lc rgb "green", 4*log(x/4)+3 with lines lw 2 lc rgb "blue"
