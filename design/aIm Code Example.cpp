

aimDIAS.Documents["Untitled"].Images(aimAll).Select();

CStorageDoc* pDoc = aimDIAS.Documents["Untitled"].GetPtr();
// Calling CaImAPIDocImages::Add (CaImAPIDocImgRange), CaImAPIDocImgRange::Select
pDoc->Images.Add(aimDIAS.Documents["Storage01"].Images(aimSelected)).Select (true);
// Calling CaImAPIDocImages::Add (CImage), CImage::Select
pDoc->Images.Add(aimDIAS.Documents["Storage01"].Images[0]).Select (true);
pDoc->Images.Add("Image01").Clear ();
