clear all;
close all;
clc;


figId=1;

%% PRR
PackageLossDistance=load('loss_package_distance.txt');
PackageTransimitDistance=load('distance.txt');

%IntersectDistance=intersect(unique(PackageLossDistance),unique(PackageTransimitDistance));
IntersectDistance=0:20:max(PackageLossDistance);

[numPackageLossDistance,centerPackageLossDistance]=hist(PackageLossDistance',IntersectDistance);
[numPackageTransimitDistance,centerPackageTransimitDistance]=hist(PackageTransimitDistance',IntersectDistance);

numPackageLossDistance=numPackageLossDistance./numPackageTransimitDistance;

figure(figId)
figId=figId+1;
plot(centerPackageLossDistance,1-numPackageLossDistance,'bo-','LineWidth',2);
title('PDR','LineWidth',2);
xlabel('Distance(m)','LineWidth',2);
ylabel('PRR','LineWidth',2);
axis([0 500 0 1]);
grid on;
