function [cell] = Create_Cell(Start, End, size,isChebysh)
if (isChebysh == 0)
    cell = Start:((End-Start)/(size - 1)):End
else
    x = 1:1:size
    cell = 0.5 * (Start + End) + 0.5 * (End - Start) * cos((2 .* x - 1) * pi / (2 * size))     
end
end

