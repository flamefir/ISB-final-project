
#ifndef KOEFFS_H_
#define KOEFFS_H_

#define SEC_PATH_KOEFFS 20
#define LOW_PASS_KOEFFS 53
#define LMS_KOEFFS 200

fract secPathKoeffs[SEC_PATH_KOEFFS] =
	{0.322366788042028r,  0.264395928385794r,  0.206066242868475r,  0.149776532650045r,
     0.097695841230382r,  0.051660017922076r,  0.013088842315497r, -0.017072109157242r,
	-0.038382133062154r, -0.050907479756676r, -0.055195360322059r, -0.052221980344917r,
	-0.043318145936232r, -0.030077203844141r, -0.014250997635853r,  0.002359899280098r,
	 0.018015211095060r,  0.031136960681540r,  0.040398700677130r,  0.044797097989259r
};

fract lowPassKoeffs[LOW_PASS_KOEFFS] =
{
-0.001038024631974r,-0.004157801694797r,-0.007305421644848r,-0.01029109908369r,
-0.01291665302744r,-0.01498508040896r,-0.01631053759925r,-0.01672822798009r,
-0.01610368252807r,-0.01434093646940r,-0.01138914807551r,-0.007247273842496r,
-0.001966504469111r,0.004349726208517r,0.01154822731400r,0.01943097429312r,
0.02776228674050r,0.03627796024889r,0.04469594795080r,0.05272810297449r,
0.06009243272787r,0.06652528319832r,0.07179286830002r,0.07570158612500r,
0.07810661956339r,0.07891840040518r,0.07810661956339r,0.07570158612500r,
0.07179286830002r,0.06652528319832r,0.06009243272787r,0.05272810297449r,
0.04469594795080r,0.03627796024889r,0.02776228674050r,0.01943097429312r,
0.01154822731400r,0.004349726208517r,-0.001966504469111r,-0.007247273842496r,
-0.01138914807551r,-0.01434093646940r,-0.01610368252807r,-0.01672822798009r,
-0.01631053759925r,-0.01498508040896r,-0.01291665302744r,-0.01029109908369r,
-0.007305421644848r,-0.004157801694797r,-0.00103802463197467r
};

#endif /* KOEFFS_H_ */
