function [y] = myfilter(b,a,x)
a = a/a(1);
na = length(a)-1; nb = length(b)-1;
order = max(na,nb);
xlength = length(x);
x = [zeros(1,order) x];
y = zeros(1,order+xlength);
for n = order:order+xlength-1
  for k = 0:nb
    y(n+1) = y(n+1)+b(k+1)*x(n-k+1);
  end
  for k = 1:na
    y(n+1) = y(n+1)-a(k+1)*y(n-k+1);
  end
end
y = y(order+1:order+xlength);
endfunction




