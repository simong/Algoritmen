/*
template <class T,class D>
bool Zoekboom<T,D>::verwijder(const T& sl){
    Zoekboom<T,D>* plaats;
    Zoekboom<T,D>* ouder;
    zoekknoop(sl,plaats,ouder);
    Zoekknoop<T,D>* weg=plaats->k;//wijst naar de uiteindelijk te verwijderen knoop
    bool gevonden=plaats->k!=0;
    if (gevonden){
    	// Er is geen linker kind, schuif het rechterkind omhoog.
        if (plaats->k->links.k==0){
            plaats->k=weg->rechts.k;
            if (plaats->k != 0)
                plaats->k->ouder=ouder;
        }
        // Er is geen rechter kind, schruif het linkerkind omhoog.
        else if (weg->rechts.k==0){
            plaats->k=weg->links.k;
            if (plaats->k != 0)
                plaats->k->ouder=ouder;
        }
        else{
            //vervangen door voorganger
            Zoekboom<T,D>* voorgangerplaats=ondervoorganger(weg);
            Zoekknoop<T,D>* voorganger=voorgangerplaats->k;
            if (voorgangerplaats!=&(weg->links)){//voorganger is niet linkerkind en dus dieper in de boom (of links van deze boom)
                voorgangerplaats->k=voorganger->links.k;
                if (voorganger->links.k !=0)
                    voorganger->links.k->ouder=voorganger->ouder;
                //geen test voor volgende twee: deze bestaan!
                plaats->k=voorganger;
                voorganger->ouder=ouder;
                voorganger->links.k=weg->links.k;
                voorganger->rechts.k=weg->rechts.k;
            }
            else{
                voorganger->rechts.k=weg->rechts.k;
                voorganger->ouder=weg->ouder;
                plaats->k=voorganger;
            }
            weg->links.k=0;
            weg->rechts.k=0;
            delete weg;
        }
        weg->links.k=0;
        weg->rechts.k=0;
        delete weg;
    }
    return gevonden;
}

//ondervoorganger mag alleen opgeroepen met pointer naar knoop
// die linkerkind heeft
template <class T,class D>
Zoekboom<T,D>* Zoekboom<T,D>::ondervoorganger(Zoekknoop<T,D>* kn){
    Zoekboom<T,D>* onder=&(kn->links);
    while (onder->k->rechts.k!=0)
        onder=&(onder->k->rechts);
    return onder;
}
*/
