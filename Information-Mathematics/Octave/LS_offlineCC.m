%�I�t���C���ŏ��j��@�ɂ��p�����[�^����
%format long
load 1prob.mat y2 % �ϑ��f�[�^
period=20
segment=period/1;
iteration=period/segment
t=linspace(0,100,2001);            %�ϑ��l�O���t�`��p���ԃX�e�b�v
t2=linspace(0,200,4001);          %����l�O���t�`��p���ԃX�e�b�v

for l=1:1:iteration
  for k=1:1:segment %�f�[�^�����������[�v
           if((segment*(1-1)+k)==1) x2=[0 0 1 0];
           elseif((segment*(1-1)+k)==2) x2=[y2(k-1,1) 0 0 1];
           else x2=[y2(k-1,1) y2(k-2,1) y2(k,2) y2(k-1,2)];
          endif

          if(k==1)
           X2=x2';
           else X2=[X2 x2']; % �Ƃ��v�Z���邽�߂̍s��X2�����
          endif
  endfor
  if(l==1) theta_hat = inv(X2*X2')*X2*y2((l-1)*segment+1:(l-1)*segment+segment,1);
  else  theta_hat = theta_hat .+ inv(X2*X2')*X2*y2((l-1)*segment+1:(l-1)*segment+segment,1);
  endif
endfor                         
  theta_hat ./= iteration

for(k=1:1:4000)
        if k>2
         u2 = u1;
         u1 =0;
          if k<=period
           zeta = [y_hat(1) y_hat(2) u2 u1];
          else
           zeta = [y_hat(1) y_hat(2) 0 0];
          endif
         y_hat=[zeta*theta_hat y_hat];           %�O���t�`��p����o�̓f�[�^�L�^
        elseif k==1
         u1=1;
         zeta = [0 0 u1 0];
         y_hat =zeta*theta_hat;
        else
         zeta = [0 0 0 u1];
         y_hat =[zeta*theta_hat y_hat];
        endif
            %���ۂ̏o�͂͊ϑ��ly2(1000��)
endfor
        plot(t(1:period),y2(1:period,1),"linewidth",5,t2(:,1:4000),y_hat(4000:-1:1),"linewidth",3);
%plot(t2(:,1:4000),y_hat(4000:-1:1),"linewidth",3);
       %�^�̃V�X�e���o�͂Ɛ���o�͂Ƃ��r

