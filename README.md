# pgnstats

get some basic statistics from (large) pgn chess games files

## build

```
make
```

## usage

```
./pgnstats --standings < Hastings1895.pgn
```
output
```
Total games: 231
Standings
found 22 players:
1.  Pillsbury, Harry Nelson         78.6%  16.5/21  (+15 -3 =3)
2.  Chigorin, Mikhail               76.2%  16.0/21  (+14 -3 =4)
3.  Lasker, Emanuel                 73.8%  15.5/21  (+14 -4 =3)
4.  Tarrasch, Siegbert              66.7%  14.0/21  (+12 -5 =4)
5.  Steinitz, William               61.9%  13.0/21  (+11 -6 =4)
6.  Schiffers, Emanuel Stepanovich  57.1%  12.0/21  (+9 -6 =6)
7.  Von Bardeleben, Curt            54.8%  11.5/21  (+8 -6 =7)
8.  Teichmann, Richard              54.8%  11.5/21  (+8 -6 =7)
9.  Schlechter, Carl                52.4%  11.0/21  (+5 -4 =12)
10. Blackburne, Joseph Henry        50.0%  10.5/21  (+9 -9 =3)
11. Walbrodt, Carl August           47.6%  10.0/21  (+6 -7 =8)
12. Mason, James                    45.2%  9.5/21  (+7 -9 =5)
13. Burn, Amos                      45.2%  9.5/21  (+8 -10 =3)
14. Janowsky, Dawid Markelowicz     45.2%  9.5/21  (+7 -9 =5)
15. Gunsberg, Isidor                42.9%  9.0/21  (+7 -10 =4)
16. Bird, Henry Edward              42.9%  9.0/21  (+4 -7 =10)
17. Marco, Georg                    40.5%  8.5/21  (+5 -9 =7)
18. Albin, Adolf                    40.5%  8.5/21  (+5 -9 =7)
19. Pollock, William Henry Kraus    38.1%  8.0/21  (+6 -11 =4)
20. Mieses, Jacques                 35.7%  7.5/21  (+4 -10 =7)
21. Tinsley, Samuel                 35.7%  7.5/21  (+7 -13 =1)
22. Vergani, Beniamino              14.3%  3.0/21  (+2 -17 =2)
```
