// Intégration au projet NKentseu : placer ces appels après l'ouverture de la fenêtre.
// API mentionnées par l'énoncé : ShowMouse, CaptureMouse, ClipMouseToClient.
// À adapter au nom exact de l'objet fenêtre dans etape5_salle.cpp.
// Exemple de logique à intégrer dans la boucle d'événements :
// window.ShowMouse(false); window.CaptureMouse(true); window.ClipMouseToClient(true);
// Sur NK_ESCAPE : relâcher, déconfiner et montrer le pointeur.
// Sur NK_F1 : si relâché, cacher/capturer/confiner ; sinon relâcher.
// Dans le chemin de fermeture, toujours exécuter les trois appels de libération.
// Cette source est une fiche d'intégration, car le type concret de fenêtre du kit
// n'est pas fourni et inventer son nom rendrait le fichier non compilable.
