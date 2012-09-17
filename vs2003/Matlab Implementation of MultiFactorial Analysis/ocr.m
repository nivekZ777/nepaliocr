clear all;
% import an image
ImagePath = 'd:\Sanjeev_SXC\Images\sata1.jpg';
Image = imread(ImagePath); 
%figure,imshow(Image);

%finding the threshold level for binary
level = graythresh(Image);
binI = im2bw(Image, level);
clear level;
%figure,imshow(binI);

% showing images
%subplot(1,2,1),imshow(Image);
%subplot(1,2,2),imshow(binI);

%toggling the binary image
bwI = ~binI;

%subplot(1,2,1),imshow(binI);
%subplot(1,2,2),imshow(bwI);

%saving the size (row and column)
[rows cols] = size(bwI);

% search for connected components 
[labeled, numObjects] = bwlabel(bwI,8);% Label components.
% show component in colours
%RGB_label = label2rgb(labeled, @spring, 'c', 'shuffle');
%imshow(RGB_label); % showing the connected component

% calculating boundingBox
graindata = regionprops(labeled,'basic');
% graindata has   Area, Centroid, BoundingBox
% BoundingBox -> [ c, r, width, height ]
% [ c, r, width, height ] = graindata(i).BoundingBox;

for i = 1:numObjects
    vectorOfWidth(i) = graindata(i).BoundingBox(3); %width
end
% The mean Bm and
% standard deviation Bs of the boundary box width are alsocomputed.
Bm = mean(vectorOfWidth);  % mean
Bs = std(vectorOfWidth,1); % standard deviation

% Computing UpperEnvelope
UpperEnvelope = uint8( zeros(rows, cols) );

for i = 1:numObjects
   tmp01 = graindata(i).BoundingBox; % tmp01 = [ c, r, width, height ]
   if tmp01(3) < Bm   % width
       continue;
   elseif tmp01(3) >= Bm+3*Bs% Bm+4*Bs
       continue;
   end
   Jst = floor( tmp01(1) );
   if (Jst < 1 )
       Jst = 1;
   end
   Jed = floor( tmp01(1)+tmp01(3) );
   Kst = floor( tmp01(2) );
   if (Kst < 1 )
       Kst = 1;
   end
   Ked = floor( tmp01(2)+tmp01(4) );
   clear j k;
   for j = Jst : Jed
        for k = Kst : Ked
            %k
            if labeled(k,j) == i
                UpperEnvelope(k,j) = 1;
                break;
            end
        end
    end
end
clear Bm Bs;
clear Jed Jst Ked Kst tmp01;
clear i j k;
clear numObjects labeled graindata;
clear vectorOfWidth;
%subplot(1,2,1),imshow(binI);
%subplot(1,2,2),imshow(double(~UpperEnvelope));

theta = 45:0.1:135; % (45 - 90 = -45) and (135 - 90 = 45)
[R,xp] = radon( UpperEnvelope,theta );
[x y] = find ( R == max( max(R) ) );
%%%%%%%%%%%%%%%
  %figure, imagesc(theta, xp, R); colormap(hot);
  %xlabel('\theta (degrees)'); ylabel('X\prime');
  %title('R_{\theta} (X\prime)');
  %colorbar
%%%%%%%%%%%%%%%
angle = 90 - theta(y);
clear theta;
clear R xp x y;
J = imrotate( bwI, angle,'bicubic' );
%subplot(1,2,1),imshow(binI);
%subplot(1,2,2),imshow(~J);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%     rotation is done %%%%%%%%%%%%%%%%%%%%%%%%%%% :: ))


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%#####################    Segmenting Line  ################################

rowI1 = sum(J')'; % calculatinng horizontal sum of each row
%figure, plot(rowI1);

[rowL, colL] = size(rowI1);

index = 1;
bool = 1; % 1 = start of a line;  0 = end of a line
if rowI1(1,1) > 0
    LineIndex(index,1) = 1; 
    bool = 0;
end

for k = 1 : rowL-1
    if bool == 1 % start of a line
        if rowI1(k,1) <= 0 & rowI1( k+1, 1) > 0
            LineIndex(index,1) = k;
            bool = 0;
        end
    else % end of a line
        if rowI1(k,1) > 0 & rowI1( k+1, 1) <= 0
            LineIndex(index,2) = k;
            bool = 1;
            index = index + 1;
        end
    end
end
% end of preprocessing of line segment
if (bool == 0 & rowI1(rowL,1) > 0 )
    LineIndex(index,2) = k;
    index = index + 1;
end
clear bool;

% calculating hieght of each line
[row col] = size(LineIndex);
for i = 1:row
    hieght(i) = LineIndex(i,2) - LineIndex(i,1);
end
% calculating average hieght of line
h = mean(hieght);

lineCorrect = 0;

for i = 2:row-1
    if hieght(i) < 3*h/5
        noLineIndex = i;
        %diffrence between this and previous line
        diff01 = LineIndex(i,1) - LineIndex(i-1,2); 
        %diffrence between this and next line
        diff02 = LineIndex(i+1,1) - LineIndex(i,2);
        
        lineCorrect = lineCorrect + 1;
        
        if diff01 < diff02
            LineIndex(i-1,2) = LineIndex(i,2);
        end        
        if diff01 >= diff02
            LineIndex(i,2) = LineIndex(i+1,2);
            noLineIndex = noLineIndex + 1;
        end
         
        [r c] = size (LineIndex);
        for j = noLineIndex : r-1
            LineIndex(j,1) = LineIndex(j+1,1);
            LineIndex(j,2) = LineIndex(j+1,2);
        end
        LineIndex(r,1) = 0;
        LineIndex(r,2) = 0;
        index = index - 1;
    end
end
clear diff01 diff02 h hieght;
clear i k;
[r c] = size (LineIndex);
for j = 1:r
    if LineIndex(j,1) ~= 0 & LineIndex(j,2) ~= 0 
        LineInfo(j).LineStart = LineIndex(j,1);
        LineInfo(j).LineEnd = LineIndex(j,2);
        LineInfo(j).LineImg = J(LineIndex(j,1):LineIndex(j,2),:);
        rwL = sum(LineInfo(j).LineImg')';
        %figure, plot(rwL);
        %calculating the head line of the sentence
        HeadLineI = find ( rwL == max(rwL) );
        LineInfo(j).HeadLineIndx = HeadLineI(1);
        clear HeadLineI rwL;
    end
end
[tmp NumberOfLine] = size (LineInfo);
clear r c j tmp;
clear lineCorrect index noLineIndex;
clear cols col colL row rowI1 rowL rows;


%lineNoForShow = 2;
%figure,imshow(LineInfo(lineNoForShow).LineImg);
%clear lineNoForShow;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Line seperation is done %%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%################### word segmentation is starting ########################
for i = 1 : NumberOfLine
    BlackLine = LineInfo(i).LineImg;
    %figure, imshow(BlackLine);

    space_con = 4;
    %minimum pixel between two word

    [lineRow lineCol] = size(BlackLine);
    linePix = sum(BlackLine);
    %figure, plot(linePix);

    spaceCount = 0;
    TotalWd_F = 1;
    bool = 1;
    for k = 1 : lineCol - 1
        if linePix(1,k) == 0
            spaceCount = spaceCount + 1;
        else
            spaceCount = 0;
        end        

        if spaceCount > space_con & linePix(1,k) == 0 & linePix(1,k+1) > 0
            wordIne_ST(TotalWd_F) = k;
            bool = 1;
            spaceCount = 0;
            TotalWd_F = TotalWd_F + 1;
        end
    end%for
    %wordIne(TotalWd) = lineCol - 1;

    spaceCount = 0;
    TotalWd_B = 1;
    bool = 1;
    for k = lineCol : -1 : 2 
        if linePix(1,k) == 0
            spaceCount = spaceCount + 1;
        else
            spaceCount = 0;
        end        

        if spaceCount > space_con & linePix(1,k) == 0 & linePix(1,k-1) > 0
            wordIne_END(TotalWd_B) = k;
            bool = 1;
            spaceCount = 0;
            TotalWd_B = TotalWd_B + 1;
        end
    end%for

    if (TotalWd_B == TotalWd_F)
        LineInfo(i).NumberOfWords = TotalWd_F-1;
        for swd = 1 : TotalWd_F-1
            WordIndex(swd,1)= wordIne_ST(swd);
            WordIndex(swd,2)= wordIne_END(TotalWd_B - swd);
            clear word BlackWord;
            LineInfo(i).VectorOfWord(swd).BlackWord(1 : lineRow, 1:WordIndex(swd,2)-WordIndex(swd,1)+1) = BlackLine(1:lineRow,WordIndex(swd,1):WordIndex(swd,2));
        end% for swd = 1 : TotalWd-1
    else
        '###########################'
        'found Error in word separate'
    end%end if if (TotalWd_B == TotalWd_F)
end
% lnNo = 2;
% WdNo = 4;
% figure, imshow(LineInfo(lnNo).VectorOfWord(WdNo).BlackWord);
% clear lnNo WdNo;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%           end of word segmentation  %%%%%%%%%%%%%%%%%%%
%#########################################################################


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                           character segmentation
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
for lnNo = 1 : NumberOfLine
    for WdNo = 1 : LineInfo(lnNo).NumberOfWords
        NonMattraWord = LineInfo(lnNo).VectorOfWord(WdNo).BlackWord;
        MattraX = LineInfo(lnNo).HeadLineIndx;
        for i = 1:4
            rowSum = sum(NonMattraWord')';
            %figure, plot(rowSum);
            MaxX = find ( rowSum == max(rowSum) );
            if ( (MaxX(1) < MattraX+3) && (MaxX(1) > MattraX-3) )
                NonMattraWord (MaxX,:)=0;
            else
                break;
            end
        end %for i = 1:5
        %figure, imshow(double(~NonMattraWord));

        [lineRow lineCol] = size(NonMattraWord);
        WordPix = sum(NonMattraWord);
        %figure, plot(WordPix);
        TotalChar_F = 1;
        spaceCount = 0;
        for k = 1 : lineCol - 1
            if WordPix(1,k) == 0
                spaceCount = spaceCount + 1;
            end

            if WordPix(1,k) == 0 & WordPix(1,k+1) > 0
                charIne_ST(TotalChar_F) = k+1;% - round(spaceCount/2);
                TotalChar_F = TotalChar_F + 1;
                spaceCount = 0;
            end
        end%for
        %charIne(TotalWd) = lineCol - 1;

        TotalChar_B = 1;
        spaceCount = 0;
        for k = lineCol : -1 : 2   
            if WordPix(1,k) == 0
                spaceCount = spaceCount + 1;
            end

            if WordPix(1,k) == 0 & WordPix(1,k-1) > 0
                charIne_END(TotalChar_B) = k-1;% + round(spaceCount/2);
                TotalChar_B = TotalChar_B + 1;
                spaceCount = 0;
            end
        end%for

        if (TotalChar_B == 1)
            VectorOfChar(1).LetteR = 0;
            break
        end

        if (TotalChar_B == TotalChar_F)
            for swd = 1 : TotalChar_F-1
                for i = 1 : lineRow 
                    for j = charIne_ST( swd ) : charIne_END( TotalChar_B-swd )        
                        LineInfo(lnNo).VectorOfWord(WdNo).VectorOfChar(swd).LetteR(i, j-charIne_ST(swd)+1) = NonMattraWord(i,j);
                        %%VectorOfChar(swd).LetteR(i, j-charIne_ST(swd)+1) = tmpp (i,j);
                    end 
                end
                %figure, imshow( double(~VectorOfChar(swd).LetteR) )
            end% for swd = 1 : TotalWd-1
        else
            'found Error in char'
        end%end if if (TotalWd_B == TotalWd_F)
    end
end

lnNo = 2;
WdNo = 1;
ChNo = 1;
figure, imshow(LineInfo(lnNo).VectorOfWord(WdNo).VectorOfChar(ChNo).LetteR);