program Lab1;

{$APPTYPE CONSOLE}
{$R *.res}

uses
  System.SysUtils,
  math;

type
  TPointer = ^TMyRec;

  TMyRec = record
    Pow: Integer;
    Coef: Integer;
    Next: TPointer;
  end;

procedure CreateList(var Header: TPointer);
var
  N, I, C: Integer;
  P, Tmp: TPointer;
begin
  write('Enter degree of polynomial: ');
  readln(N);
  new(Header);
  new(P);
  if N >= 0 then
  begin
    write('Enter coefficient at x^', N, ': ');
    readln(C);
    if C <> 0 then
    begin
      Header^.Next := P;
      P^.Pow := N;
      P^.Coef := C;
    end
    else
      P := Header;
  end;
  for I := 1 to N do
  begin
    write('Enter coefficient at x^', N - I, ': ');
    readln(C);
    if C <> 0 then
    begin
      new(Tmp);
      P^.Next := Tmp;
      Tmp^.Pow := N - I;
      Tmp^.Coef := C;
      P := Tmp;
    end;
  end;
  P^.Next := nil;
end;

procedure PrintList(P: TPointer);
begin
  P := P^.Next;
  if P <> nil then
  begin
    if (P^.Pow <> 0) and (P^.Coef = 1) then
      write('x^', P^.Pow)
    else if (P^.Pow <> 0) and (P^.Coef = -1) then
      write('-x^', P^.Pow)
    else if (P^.Pow = 1) then
      write(P^.Coef, 'x')
    else if (P^.Pow = 0) then
      write(P^.Coef)
    else
      write(P^.Coef, 'x^', P^.Pow);
    P := P^.Next;
  end;
  while (P <> nil) do
  begin
    if (P^.Pow <> 0) and (P^.Coef = 1) then
      write(' + ', 'x^', P^.Pow)
    else if (P^.Pow <> 0) and (P^.Coef = -1) then
      write(' - ', 'x^', P^.Pow)
    else if (P^.Pow = 1) and (P^.Coef > 0) then
      write(' + ', P^.Coef, 'x')
    else if (P^.Pow = 1) and (P^.Coef < 0) then
      write(' - ', Abs(P^.Coef), 'x')
    else if (P^.Pow = 0) and (P^.Coef > 0) then
      write(' + ', P^.Coef)
    else if (P^.Pow = 0) and (P^.Coef < 0) then
      write(' - ', Abs(P^.Coef))
    else if (P^.Coef > 0) then
      write(' + ', P^.Coef, 'x^', P^.Pow)
    else if (P^.Coef < 0) then
      write(' - ', Abs(P^.Coef), 'x^', P^.Pow);
    P := P^.Next;
  end;
  writeln;
end;

function Equality(P: TPointer; Q: TPointer): Boolean;
var
  Flag: Boolean;
begin
  Flag := True;
  P := P^.Next;
  Q := Q^.Next;
  if (P <> nil) and (Q <> nil) and (P^.Pow <> Q^.Pow) then
    Flag := False;
  while Flag and (P <> nil) and (Q <> nil) do
  begin
    if (P^.Pow <> Q^.Pow) or (P^.Coef <> Q^.Coef) then
      Flag := False;
    P := P^.Next;
    Q := Q^.Next;
  end;
  result := Flag;
end;

function Meaning(P: TPointer; X: Double): Double;
begin
  P := P^.Next;
  result := 0;
  while (P <> nil) do
  begin
    result := result + P^.Coef * Power(X, P^.Pow);
    P := P^.Next;
  end;
end;

procedure Add(var P: TPointer; Q: TPointer; R: TPointer);
var
  N, I, C: Integer;
  Tmp, tmp1: TPointer;
begin
  Q := Q^.Next;
  R := R^.Next;
  N := max(Q^.Pow, R^.Pow);
  new(P);
  new(Tmp);
  if N >= 0 then
  begin
    Tmp^.Pow := N;
    P^.Next := Tmp;
  end;

  while (Q <> nil) or (R <> nil) do
  begin
    C := 0;
    if (Q <> nil) and (Q^.Pow = Tmp^.Pow) then
    begin
      C := C + Q^.Coef;
      Q := Q^.Next;
    end;
    if (R <> nil) and (R^.Pow = Tmp^.Pow) then
    begin
      C := C + R^.Coef;
      R := R^.Next;
    end;
    Tmp^.Coef := C;
    if (Q <> nil) or (R <> nil) then
    begin
      new(tmp1);
      Tmp^.Next := tmp1;
      Tmp := tmp1;
    end;
    if (Q = nil) and (R <> nil) then
      Tmp^.Pow := R^.Pow
    else if (Q <> nil) and (R = nil) then
      Tmp^.Pow := Q^.Pow
    else if (Q <> nil) and (R <> nil) then
      Tmp^.Pow := max(Q^.Pow, R^.Pow);
  end;
  Tmp^.Next := nil;
end;

var
  Task, X: Integer;
  P, Q, R: TPointer;

begin
  Task := 1;
  while Task <> 0 do
  begin
    writeln('Choose an action: ');
    writeln('1 - Check polynomial equality');
    writeln('2 - Calculate the value of a polynomial');
    writeln('3 - Add two polynomials');
    writeln('0 - Exit');
    readln(Task);
    case Task of
      1:
        begin
          CreateList(P);
          writeln('Polynomial P:');
          PrintList(P);
          CreateList(Q);
          writeln('Polynomial Q:');
          PrintList(Q);
          if (Equality(P, Q)) then
            writeln('Polynomials are equal')
          else
            writeln('Polynomials are not equal');
        end;
      2:
        begin
          CreateList(P);
          writeln('Polynomial P:');
          PrintList(P);
          write('Enter x: ');
          readln(X);
          writeln('The result is: ', Meaning(P, X):10:4);
        end;
      3:
        begin
          CreateList(Q);
          writeln('Polynomial Q:');
          PrintList(Q);
          CreateList(R);
          writeln('Polynomial R:');
          PrintList(R);
          Add(P, Q, R);
          writeln('The result is:');
          PrintList(P);
        end;
    end;
  end;

end.
