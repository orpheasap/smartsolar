void regression(float x[], float y[], int n, float* a, float* b) {
    
    float Sx=0, Sy=0, Sxy=0, Sxx=0;
    int i;
    
    for(i=0; i<n; i++) {
        Sx += x[i];
        Sy += y[i];
        Sxy += x[i]*y[i];
        Sxx += x[i]*x[i];
    }
    *a = (n*Sxy - Sx*Sy) / (n*Sxx - Sx*Sx);
    *b = (Sy*Sxx - Sx*Sxy) / (n*Sxx - Sx*Sx);
}
