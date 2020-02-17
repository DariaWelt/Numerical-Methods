dll_path = "../dll/T.dll"
h_path = "../dll/Interpolation.h"
loadlibrary(dll_path, h_path)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    EQUABLE    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure
x = Create_Cell(0,3,15,0)
x1 = Create_Cell(0,3,100,0)
y = Hermit_Interpolation(x, x1, @fun, @fun1)
plot(x1,y)
grid on
hold on
plot(x1,fun(x1),"r")
plot(x,fun(x),"*b")
xlabel("x")
ylabel("y")
title("Hermit interpolation for 15 points on equable cell")
legend("exp(sin(x))","Hermit Polynom","plots")

figure 
semilogy(x1,abs(fun(x1)-y),"b")
grid on
hold on
xlabel("x")
ylabel("error = max(f(x) - H(x))")
title("loss function(Hermit for 15 points, equable cell)")



figure
x = Create_Cell(0,3,50,0)
y = Hermit_Interpolation(x, x1, @fun, @fun1)
plot(x1,y)
grid on
hold on
plot(x1,fun(x1),"r")
plot(x,fun(x),"*b")
xlabel("x")
ylabel("y")
ylim([-5,5])
title("Hermit interpolation for 50 points on equable cell")
legend("exp(sin(x))","Hermit Polynom","plots")

figure 
semilogy(x1,abs(fun(x1)-y),"b")
grid on
hold on
xlabel("x")
ylabel("error = max(f(x) - H(x))")
title("loss function(Hermit for 50 points, equable cell)")


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  CHEBYSHEV    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure
x = Create_Cell(0,3,17,1)
x1 = Create_Cell(0,3,100,0)
y = Hermit_Interpolation(x, x1, @fun, @fun1)
plot(x1,y)
grid on
hold on
plot(x1,fun(x1),"r")
plot(x,fun(x),"*b")
xlabel("x")
ylabel("y")
title("Hermit interpolation for 17 points on Chebyshev cell")
legend("exp(sin(x))","Hermit Polynom","plots")

figure 
semilogy(x1,abs(fun(x1)-y),"b")
grid on
hold on
xlabel("x")
ylabel("error = max(f(x) - H(x))")
title("loss function(Hermit for 17 points, Chebyshev cell)")


figure
x = Create_Cell(0,3,50,1)
y = Hermit_Interpolation(x, x1, @fun, @fun1)
plot(x1,y)
grid on
hold on
plot(x1,fun(x1),"r")
plot(x,fun(x),"*b")
xlabel("x")
ylabel("y")
title("Hermit interpolation for 50 points on Chebyshev cell")
legend("exp(sin(x))","Hermit Polynom","plots")

figure 
semilogy(x1,abs(fun(x1)-y),"b")
grid on
hold on
xlabel("x")
ylabel("error = max(f(x) - H(x))")
title("loss function(Hermit for 50 points, Chebyshev cell)")

clear all
unloadlibrary('T')