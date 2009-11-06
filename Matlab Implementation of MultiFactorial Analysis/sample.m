clear all;
impath='d:\Sanjeev_SXC\images\naha.jpg';    % setting the image path
imgtest=imread(impath);                     % reading the image
imshow(imgtest);                            % Displaying the orginal image

level=graythresh(imgtest);                  % Calculating the threshold value for the binarisation of image
binI=im2bw(imgtest,level);                  % Converting original into the logical array binary image
clear level;
bwI=~binI;                                  % Negating the binary image

[rows cols]=size(bwI)                       % Calculating the size of image 'bwI'
subplot(5,5,1),imshow(binI);                % Plotting both the binary images
subplot(5,5,2),imshow(bwI);

%%%%%%%%%%%Calculation of the Left Margin and Right Margin of the actual
%%%%%%%%%%%character in the negated Binary Image
rcount=0;
for j= 1:rows
    flag=0;
    for i=1:cols
        temp=bwI(j,i);
        if(temp==1 && flag==0)
            mincol(j)=i;
            flag=1;
         elseif(temp==1)
            maxcol(j)=i;
            rcount=j;
        end
    end
end
for k=1:rcount
    if(mincol(k)==0)
        mincol(k)=max(mincol);
    end
end
leftcol=min(mincol);            % left margin for the character in the image
rightcol=max(maxcol);           % Right margin for the character in the image
leftcol
rightcol
clear i;
clear j;
clear flag;
clear temp;

%%%%%%%%%%%%%%%%%% End of Margin Calculation %%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%% Left Margin in variable leftcol 
%%%%%%%%%%%%%%%% Right Margin in variable

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%% Calculation of the Header Start Row and Header Size of Character in the Image
for j= 1:rows
    ccount=0;
    for i=1:cols
        temp=bwI(j,i);
        if(temp==1)
            ccount=ccount+1;
        end
    end
    RowCount(j)=ccount;
end
RowCount
uper=max(RowCount);
uper                % maximum pixel value indicating Header Presence Detected
for z=1:rows
    if (RowCount(z)==uper)
        ubound=z;
        break;
    end
end
HeaderSize=0;
for zz=1:rows
    if (RowCount(zz)==uper)
        HeaderSize=HeaderSize+1;
    end
end
HeaderSize          % header size calculated
ubound              % Starting Row of Header
clear i;
clear j;
clear zz;
clear ccount;
clear z;
urange=ubound+HeaderSize;   % Range of Header

%%%%%%%%%% END OF HEADER SIZE AND POSITION DETERMINATION %%%%%%%%%%

%%%%%%%%%% START OF UPPER AND LOWER BOUNDARY OF MIDDLE RANGE OF IMAGE %%%%
%%%%%%%%%% AND THE BLOB THICKNESS AT EACH COLUMN OF THE IMAGE %%%%%%%%%%%

for j= 1:cols
    flag=0;
    tempx=0;
    tempy=0;
    for i=urange:rows
        temp=bwI(i,j);
        if(temp==1 && flag==0)
            mini(j)=i;
            flag=1;
            tempx=i;
        elseif(temp==1)
            maxm(j)=i;
            tempy=i;
        end
    end
    blob(j,1)=tempx;            % UPPER STARTING POSITION OF BLOB
    blob(j,2)=tempy;            % LOWER STARTING POSITION OF BLOB
end
upper=max(mini);                % UPPER BOUNDARY OF MIDDLE REGION OF IMAGE
lower=max(maxm);                % LOWER BOUNDARY OF MIDDLE REGION OF IMAGE
upper
lower
blob
T=lower-ubound;                 % SIZE OF THE MIDDLE REGION
clear i;
clear j;
clear tempx;
clear tempy;

%%%%%%%%%%%%%%%%%%% START OF REMOVING THE HEADER FROM THE CHARACTER IMAGE
for j= 1:cols
    for i=0:HeaderSize-1
        bwI(ubound+i,j)=0;
    end
end
subplot(5,5,3),imshow(bwI); % PLOTTING THE IMAGE WITHOUT HEADER

%%%%%%%%%%%%%% START OF MULTIPLE FACTORIAL CALCULATION AND ANALYSIS %%%%

%%%%%%%%%%%%%% CALCULATION OF FACTOR 1:
%%%%%%%%%%%%%%  PIXEL TRANSITION FROM WHITE TO BLACK
for j= 1:cols
    count(j)=0;
    for i=1:rows-1
        temp=bwI(i,j);
        temp1=bwI(i+1,j);
        if(temp~=temp1)
            count(j)=count(j)+1;
        end
    end
    if(count(j)~=0)
        Fic(j)=1/count(j);      % FORMULA TO CALCULATE Fic FACTOR
    else
        Fic(j)=0;
    end
end
count
Fic                             % ARRAY OF FIRST FACTOR CALCULATION
clear i;
clear count;
clear j;
%%%%%%%%%%%%%%%% END OF FACTOR 1 CALCULATION %%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%% CALCULATION OF FACTOR 2:
%%%%%%%%%%%%%%% BLOB THICKNESS FACTOR %%%%%%%%%%%%%%%%%%%%
for j= 1:cols
    t(j)=0;
    for i=urange:lower
        temp=bwI(i,j);
        if(temp==1)
            t(j)=t(j)+1;
        end
    end
    Fmt(j)=1-t(j)/T;  % FORMULA TO CALCULATE FACTOR 2
end
Fmt                     % ARRAY OF SECOND FACTOR CALCULATION
%plot(t);
clear j;
clear i;
clear temp;
%%%%%%%%%%%%%%%%%%% END OF FACTOR 2 CALCULATION %%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%% CALCULATION OF FACTOR 3 %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%% DEGREE OF MIDDLENESS ROW-WISE %%%%%%%%%%%%%

for m=1:cols
    l1=blob(m,1)-urange;
    l2=lower-blob(m,2);
    Fdm(m)=min(l1,l2)/max(l1,l2); % FORMULA TO CALCULATE FACTOR 3
end
Fdm                     % ARRAY OF THIRD FACTOR CALCULATION

clear m;
%%%%%%%%%%%%%%%%%%%%%% END OF FACTOR 3 CALCULATION %%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%% CALCULATION OF FACTOR 4 %%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%% DEGREE OF MIDDLENESS COLUMN-WISE
mid=(leftcol+rightcol)/2;
for m=1:cols
    if (m<mid)
        Fdmc(m)=m-mid;  
    elseif(mid<m)
        Fdmc(m)=mid-m;
    end
end
Fdmc  % ARRAY OF 4TH FACTOR CALCULATION

clear m; 
    %%%%%%%%%%%%%%%%%%%% END OF FACTOR CALCULATION%%%%%%%%%%%%

%%%%%%%%%%%%%%% PREPARING MULTIFACTORIAL TABLE %%%%%%%%%%%%%%%%%%%
for i=1:4
    for j=1:cols
       if(i==1)
           Vs(i,j)=Fic(j);
       elseif(i==2)
            Vs(i,j)=Fmt(j);
       elseif(i==3)
            Vs(i,j)=Fdm(j);
       elseif(i==4)
           Vs(i,j)=Fdmc(j);
       end
    end
end

clear i;
clear j;
%%%%%%%%%%%%%% MULTIFACTORIAL ARRAY OF SIZE 4xCOLS PREPARED %%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%% PREPARING 1xCOLS MATRIX AFTER  MULTIFACTPRIAL EVALUATION
for i=1:cols
    sum=0;
    for j=1:4
        sum=sum+Vs(j,i);
    end
    Vfs(i)=sum/4;
end
    
Vfs % REQUIRED ARRAY AFTER MULTIFACTORIAL EVLAUATION

% IDENTIFYING THE CUT COLUMN BY SELECTING THE HIGHEST VALUE IN Vfs TABLE
%COLUMN WITH THE HIGHEST VALUE AT Vfs TABLE IS FIRST CUT COLUMN
    pos=0;
    mmax=max(Vfs);
    mmax
    for l=1:cols
        if(Vfs(l)==mmax)
          pos=l;
        end
    end         % IDENTIFYING THE FIRST CUT CULUMN
    bwI2=bwI;
    
    %%%%%%%%%%%%%%% SELECTING THE FIRST PART OF THE IMAGE AFTER SEGEMENTING
    %%%%%%%%%%%%%%% AT CUT COLUMN
    for i=1:rows
        for j=leftcol:pos-1
            part1(i,j)=bwI(i,j);
        end
    end
    %%%%%%%%%%%%% INSERTING BLANK COLUMN BETWEEN TWO RESULSTANT IMAGES
    for k=1:rows
        bwI2(k,pos)=0;
    end
    %%%%%%%%%%%%% APPENDING REMAINING PART OF IMAGE AFTER SEGMENTATION
    for i=1:rows
        for j=pos+1:rightcol
            part1(i,j+1)=bwI(i,j);
        end
    end
    for j=1:cols
        part1(rows+1,j)=0;
    end
    p1=~part1;
    subplot(5,5,6),imshow(p1);
    imwrite(p1,'p1.jpg');       %  PREPARING A IMAGE FILE FOR RESULTANT DATA
    Vfs(pos)=0;
    Vfs
clear l k i j i pos mmax bwI2;

%%%%%%%%%%%%%%READY TO SEND THE IMAGE TO CLASSIFIER |%%%%%%%%%%%%%%%%%%%%




        