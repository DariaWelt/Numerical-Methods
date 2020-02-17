function [y] = Hermit_Interpolation(train, test, fun, fun1)
    f = fun(train)
    f1 = fun1(train)
    table_fun = calllib('T','CreateTableFunc', train, f, f1, length(train))
    y = calllib('T','Hermit', test, length(test), table_fun)
    setdatatype(y,'doublePtr',length(test))
    y = y.val'
end

