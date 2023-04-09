program Lab3;

{$APPTYPE CONSOLE}
{$R *.res}

uses
  System.SysUtils,
  Math;

type
  PsymbolStack = ^TSymbolStack;

  TSymbolStack = record
    Symbol: Char;
    Priority: Integer;
    Next: PsymbolStack;
  end;

  PValStack = ^TValStack;

  TValStack = record
    Val: Real;
    Next: PValStack;
  end;

  TArrEl = record
    Val: Real;
    IsSet: Boolean;
  end;

function GetPriority(C: Char): Integer;
begin
  if (C >= 'a') and (C <= 'z') then
    result := 7
  else
  begin
    case C of
      '+', '-':
        result := 1;
      '*', '/':
        result := 3;
      '^':
        result := 6;
      '(':
        result := 9;
    end;
  end;
end;

function GetStackPriority(C: Char): Integer;
begin
  if (C >= 'a') and (C <= 'z') then
    result := 8
  else
  begin
    case C of
      '+', '-':
        result := 2;
      '*', '/':
        result := 4;
      '^':
        result := 5;
      '(':
        result := 0;
    end;
  end;
end;

function PushSymbol(Top: PsymbolStack; C: Char; Pr: Integer): PsymbolStack;
var
  Tmp: PsymbolStack;
begin
  new(Tmp);
  Tmp^.Symbol := C;
  Tmp^.Priority := Pr;
  Tmp^.Next := Top;
  result := Tmp;
end;

function PushVal(Top: PValStack; Val: Real): PValStack;
var
  Tmp: PValStack;
begin
  new(Tmp);
  Tmp^.Val := Val;
  Tmp^.Next := Top;
  result := Tmp;
end;

procedure PopSymbol(var Top: PsymbolStack);
var
  Tmp: PsymbolStack;
begin
  if Top <> nil then
  begin
    Tmp := Top;
    Top := Top^.Next;
    Dispose(Tmp);
  end;
end;

procedure PopVal(var Top: PValStack);
var
  Tmp: PValStack;
begin
  if Top <> nil then
  begin
    Tmp := Top;
    Top := Top^.Next;
    Dispose(Tmp);
  end;
end;

var
  B, A: Real;
  CurrPr, CurrStackPr, Rang, I: Integer;
  Values: array ['a' .. 'z'] of TArrEl;
  ValStack: PValStack;
  SymbolStack: PsymbolStack;
  Str, Answ: string;

begin
  ValStack := nil;
  new(SymbolStack);
  SymbolStack^.Priority := -1;
  readln(Str);
  I := 1;
  while I <= Length(Str) do
  begin
    if Str[I] = ')' then
    begin
      while SymbolStack^.Symbol <> '(' do
      begin
        Answ := Answ + SymbolStack^.Symbol;
        PopSymbol(SymbolStack);
      end;

      PopSymbol(SymbolStack);
      Inc(I);
    end
    else
    begin
      CurrPr := GetPriority(Str[I]);
      CurrStackPr := GetStackPriority(Str[I]);

      while (CurrPr <= SymbolStack^.Priority) do
      begin
        Answ := Answ + SymbolStack^.Symbol;
        PopSymbol(SymbolStack);
      end;

      SymbolStack := PushSymbol(SymbolStack, Str[I], CurrStackPr);
      Inc(I);

    end;
  end;

  while SymbolStack^.Priority <> -1 do
  begin
    Answ := Answ + SymbolStack^.Symbol;
    PopSymbol(SymbolStack);
  end;

  Rang := 0;

  for I := 1 to Length(Answ) do
    if (Answ[I] >= 'a') and (Answ[I] <= 'z') then
      Inc(Rang)
    else
      dec(Rang);

  writeln('Rang = ', Rang);
  if Rang = 1 then
  begin
    writeln('Reverse notation: ', Answ);

    I := 1;
    while I <= Length(Answ) do
    begin
      if (Answ[I] >= 'a') and (Answ[I] <= 'z') then
      begin
        if (not Values[Answ[I]].IsSet) then
        begin
          write(Answ[I], ' = ');
          readln(Values[Answ[I]].Val);
          Values[Answ[I]].IsSet := true;
        end;

        ValStack := PushVal(ValStack, Values[Answ[I]].Val);
      end
      else
      begin
        B := ValStack^.Val;
        PopVal(ValStack);
        A := ValStack^.Val;
        PopVal(ValStack);

        case Answ[I] of
          '+':
            ValStack := PushVal(ValStack, A + B);
          '-':
            ValStack := PushVal(ValStack, A - B);
          '*':
            ValStack := PushVal(ValStack, A * B);
          '/':
            ValStack := PushVal(ValStack, A / B);
          '^':
            ValStack := PushVal(ValStack, Power(A, B));
        end;
      end;
      Inc(I);
    end;
    writeln('Result: ', ValStack^.Val:10:4);

  end;
  readln;

end.
