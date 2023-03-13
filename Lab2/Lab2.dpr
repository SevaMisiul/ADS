program Lab2;

{$APPTYPE CONSOLE}
{$R *.res}

uses
  System.SysUtils;

type
  TPointer = ^TMyRec;

  TMyRec = record
    Name: string;
    TelNumber: string;
    Next: TPointer;
  end;

procedure CreateList(P: TPointer);
var
  N, I, J: Integer;
  S: string;
  Flag: Boolean;
  Tmp: TPointer;
begin
  write('Enter number of subscribers: ');
  readln(N);
  for I := 1 to N do
  begin
    Flag := False;
    writeln(I, ' subscriber');
    while not Flag do
    begin
      write('Enter name: ');
      readln(S);
      Flag := True;
      J := 1;
      while Flag and (J <= S.Length) do
      begin
        if ((S[J] < 'A') or (S[J] > 'z')) or ((S[J] > 'Z') and (S[J] < 'a'))
        then
          Flag := False;
        Inc(J);
      end;
    end;
    P^.Name := S;

    Flag := False;
    while not Flag do
    begin
      write('Enter telephone number of subscriber: ');
      Flag := True;
      readln(S);
      if S.Length <> 7 then
        Flag := False
      else
        for J := 1 to 7 do
          if (S[J] < '0') or (S[J] > '9') then
            Flag := False;
    end;
    P^.TelNumber := S;

    Tmp := P;
    new(P);
    Tmp.Next := P;
  end;
  Tmp^.Next := nil;
end;

procedure SortList(P: TPointer);
var
  J, Tmp, Start: TPointer;
begin
  Start := P;
  while P <> nil do
  begin
    J := Start;
    while J^.Next <> nil do
    begin
      if (J^.Next^.Name < J^.Name) then
      begin
        new(Tmp);
        Tmp^.Name := J^.Next.Name;
        Tmp^.TelNumber := J^.Next.TelNumber;

        J^.Next^.Name := J^.Name;
        J^.Next^.TelNumber := J^.TelNumber;

        J^.Name := Tmp^.Name;
        J^.TelNumber := Tmp^.TelNumber;
      end;
      J := J^.Next;
    end;
    P := P^.Next;
  end;

end;

procedure PrintList(P: TPointer);
var
  I: Integer;
begin
  I := 1;
  P := P^.Next;
  writeln;
  while P <> nil do
  begin
    writeln(I, ' subscriber');
    writeln('Name: ', P^.Name);
    writeln('Telephone number : ', P^.TelNumber);
    writeln;
    Inc(I);
    P := P^.Next;
  end;
end;

procedure SearchByName(P: TPointer; Name: string);
var
  I: Integer;
begin
  I := 0;
  P := P^.Next;
  while P <> nil do
  begin
    if P^.Name = Name then
    begin
      Inc(I);
      writeln('Name: ', P^.Name);
      writeln('Telephone number : ', P^.TelNumber);
      writeln;
    end;
    P := P^.Next;
  end;
  if I = 0 then
    writeln('No matches found');
end;

procedure SearchByTel(P: TPointer; Tel: string);
var
  I: Integer;
begin
  I := 0;
  P := P^.Next;
  while P <> nil do
  begin
    if P^.TelNumber = Tel then
    begin
      Inc(I);
      writeln('Name: ', P^.Name);
      writeln('Telephone number : ', P^.TelNumber);
      writeln;
    end;
    P := P^.Next;
  end;
  if I = 0 then
    writeln('No matches found');
end;

var
  Task: Integer;
  Header, P: TPointer;
  S: string;

begin
  Task := 1;
  while Task <> 0 do
  begin
    writeln('Choose an action: ');
    writeln('1 - Create list');
    writeln('2 - Print list');
    writeln('3 - Search by name');
    writeln('4 - Search by telephone number');
    writeln('0 - Exit');
    readln(Task);
    case Task of
      1:
        begin
          new(Header);
          new(P);
          Header^.Next := P;
          CreateList(P);
          SortList(Header^.Next);
        end;
      2:
        begin
          if Header <> nil then
            PrintList(Header)
          else
            writeln('You must create list');
        end;
      3:
        begin
          if Header <> nil then
          begin
            writeln('Enter name: ');
            readln(S);
            writeln;
            SearchByName(Header, S);
          end
          else
            writeln('You must create list');
        end;
      4:
        begin
          if Header <> nil then
          begin
            writeln('Enter telephone number: ');
            readln(S);
            writeln;
            SearchByTel(Header, S);
          end
          else
            writeln('You must create list');
        end;
    end;
  end;

end.
