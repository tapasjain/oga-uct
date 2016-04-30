function calc_score_percent_sailing(domain,count)
total_score=zeros(count+1,3)
%domain='acadadvising'
%domain='navigation'
%domain='race'
%domain='sysadmin'
for m=0:count
    n=10+m*5   
    asap=dlmread(strcat('RESULTS_',domain,'/ALL',int2str(n),'/asapNew.txt'),' ');
    base=dlmread(strcat('RESULTS_',domain,'/ALL',int2str(n),'/baseNew.txt'),' ');
    ogak1=dlmread(strcat('RESULTS_',domain,'/ALL',int2str(n),'/ogaNew.txt'),' ');
    temp=zeros(3,1);
    temp(1,1)=ogak1(size(ogak1,1),4);
    temp(2,1)=base(size(base,1),4);
    temp(3,1)=asap(size(asap,1),4);
    max_time=min(temp);
    asapReg=zeros(6,1);
    baseReg=zeros(6,1);
    ogak1Reg=zeros(6,1);
    for i=1:6
        val=i*max_time/6;
        for j=2:size(asap,1)
            if(val<asap(j,4))
                break;
            end
        end
        asapReg(i,1)=asap(j-1,2)+(val-asap(j-1,4))*(asap(j,2)-asap(j-1,2))/(asap(j,4)-asap(j-1,4));
        for j=2:size(base,1)
            if(val<base(j,4))
                break;
            end
        end
        baseReg(i,1)=base(j-1,2)+(val-base(j-1,4))*(base(j,2)-base(j-1,2))/(base(j,4)-base(j-1,4));
         for j=2:size(ogak1,1)
            if(val<ogak1(j,4))
                break;
            end
        end
        ogak1Reg(i,1)=ogak1(j-1,2)+(val-ogak1(j-1,4))*(ogak1(j,2)-ogak1(j-1,2))/(ogak1(j,4)-ogak1(j-1,4));
    end
    score_mat=zeros(6,3);
    score_mat(:,3)=ogak1Reg(:,1);
    score_mat(:,2)=asapReg(:,1);
    score_mat(:,1)=baseReg(:,1);
    for l=1:6
        score_mat(l,3)=score_mat(l,3)/score_mat(l,1);
        score_mat(l,2)=score_mat(l,2)/score_mat(l,1);
        score_mat(l,1)=score_mat(l,1)/score_mat(l,1);
    end
    score_mat=score_mat*100;
    
    
    total_score(m+1,1)=sum(score_mat(:,1));
    total_score(m+1,2)=sum(score_mat(:,2));
    total_score(m+1,3)=sum(score_mat(:,3));
end
total_score/=6;
total_score-=100
sdev=2*std(total_score,1)/sqrt(count+1)
mean(total_score,1)

        
            
                
                
        

    
