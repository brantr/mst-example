fdata = "mst.dat"
openr,1,fdata
n= long64(0)
readu,1,n
x= fltarr(3,n)
y= fltarr(3,n)
dis= fltarr(n)
eid= lon64arr(n)
idxA= lon64arr(n)
idxB= lon64arr(n)
readu,1,x
readu,1,y
readu,1,dis
readu,1,eid
readu,1,idxA
readu,1,idxB
close,1

fdata = "st.dat"
openr,1,fdata
nst = long64(0)
readu,1,nst
xst= fltarr(3,nst)
yst= fltarr(3,nst)
disst= fltarr(nst)
eidst= lon64arr(nst)
idxAst= lon64arr(nst)
idxBst= lon64arr(nst)
readu,1,xst
readu,1,yst
readu,1,disst
readu,1,eidst
readu,1,idxAst
readu,1,idxBst
close,1

xmin = 1.1*min(x)
xmax = 1.1*max(x)
if abs(xmin) gt xmax then begin
  xmax = -1.0*xmin
endif else begin
  if xmin lt 0 then begin
    xmin = -1.0*xmax
  endif
endelse
ymin = xmin
ymax = xmax

test = set_psym_circle()
device,decompose=0
window,2,xsize=600,ysize=600
plot,[0],[0],xrange=[xmin,xmax],yrange=[ymin,ymax],xstyle=1,ystyle=1
xx = fltarr(2)
yy = fltarr(2)
for i=0,nst-1 do begin
  xx(0) = xst(0,i)
  xx(1) = yst(0,i)
  yy(0) = xst(1,i)
  yy(1) = yst(1,i)
  oplot,xx,yy
endfor
loadct,13,/silent
for i=0,n-1 do begin
	xx(0) = x(0,i)
	xx(1) = y(0,i)
	yy(0) = x(1,i)
	yy(1) = y(1,i)
	oplot,xx,yy,color = (255.-40.)*float(i)/float(n-1)+40., thick=3
endfor
loadct,0,/silent
;oplot,x(0,*),x(1,*),psym=8
;oplot,y(0,*),y(1,*),psym=8


for i=0,n-1 do begin
  print,idxA(i),idxB(i)
endfor
end