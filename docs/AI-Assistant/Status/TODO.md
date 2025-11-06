#### file: TODO.md

# DO NOW LIST:
- En animation modes `pulse` y `wave` de organicText funcionan animando los puntos segun una funcion relativa a un punto horizontalmente centrado en el texto dibujado. me gustaria qeye pudiera modificarse el punto x desde la izquiera a la derecha, donde 0.5 sea el centro como hace ahora. tambien podemos usarlo para el modo `orbit` haciendo rotar desde otro x y no siempre desde el centro. anade otro ofparam 0-1 llamado animOriginX o similar.


## REMEMBER:
- lee AI-AGENTS-GUIDE.md (AGENTS.md y RULES.md principalmente)
- hazme propuestas antes de implementar nada
- ignora los TODO incrustados en el codigo!
- revisa y modifica solo /src, principalmente src/organicText.h/cpp, y si es necesario ofapp.h/.cpp
- no toques main.cpp
- si necesitas (y te autorizo) ejecutar la app usa Debug ya que Release no esta bien configurado

# DONE: CHANGELOG:
- he actualizado y mejorado ofxTweenLiteHelper. puedes ver el ejemplo de uso en ofxTweenLite/example4/src. revisa e implementa estas nuevas mejoras en organicText.h/.cpp y si necesitas toca cosas en ofapp

# IGNORE: NOTES:
- no toques ofxTweenLiteHelper a no ser que sea imprescindible y yo te lo indique.
- no toques nunca ofxTweenLite.h
- En el grupo de params `color modes` de `organicText`hay algunos parametros nuevos que querria anadir y exponer que ahora son internos hardocodeados en organicText.h/cpp.
- en la funcion ofColor OrganicText::getPointColor( ) modo case COLOR_GLOBAL_MIX y case COLOR_DISTANCE: se hacen usos de estas variables que quiero exponer publicas como ofParams en el grupo de params `color modes`:
- mira estas constantes en organicText.h:
// Color Constants
constexpr float COLOR_DISTANCE_MAX = 250.0f;
constexpr float COLOR_DISTANCE_INNER = 0.4f;
constexpr float COLOR_DISTANCE_MIDDLE = 0.7f;
constexpr float COLOR_ALPHA_CENTER = 255.0f;
constexpr float COLOR_ALPHA_EDGE = 80.0f;
- piensa cuales de estas variables podriamos colocar como ofParams publicos en el grupo de params `color modes` de organicText, y cuales no. no es necesario implementar callbacks ya que estas variables solo se usan en la funcion getPointColor() que se llama cada frame.
- crea estos ofParams junto a ofParameter<float> colorMixFactor; deben ser normalizados entre 0 y 1. y puedes mantener o definir unas constantes min max hardcodeadas en organicText.h.
- intenta entender el algoritmo y como funcionan estas variables en la funcion getPointColor() para ver si tiene sentido exponerlas o no: asi podemos empezar creando las 3 variables en ofparams mas importantes.
- lo importante de estos dos modos es que usan los 3 colores globales (color1, color2, color3) y los mezclan segun la distancia al centro del texto y la posicion del punto en el texto.