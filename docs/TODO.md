#### file: TODO.md

# DO NOW LIST:
[ ] 

# DO NEXT LIST: (don't do now. could have semi finished job tasks)
[ ] 

----

# ALREADY DONE: CHANGELOG:
[ ] LAS PARTICLES SE CREAN BIEN PERO NO TIENEN EFECTO SOBRE LOS POINTS, POR TANTO NO DEFORMAN COMO ANTES LO TENIA YO. MOUSE AS MODIFIER QUE HAS ANADIDO NO ERA NECESARIO: YA QUE TENEMOS `MOUSE TWEAKS`. ESE TOGGLE BOOL DEBE SER COMO ANTES `PARTICLE MODIFIER`. EL TIPO DE MODIFICACION -INTENSIDAD Y RADIO- QUE HACE EL MOUSE, DEBE SER USADO Y AFECTAR IGUAL EN LAS PARTICLES. LA CAJAS DE LAS PARTICLES TODAS BLANCAS SIN COLORES Y ALPHA AL 50%.. OJO. SE HA ROTO LA ACTUACION DE `PARTICLES TWEAKS`. ARREGLALO Y ADEMAS ANADE PARA QUE PUEDA HABER UN VECTOR DE VARIOS PUNTOS ANIMADOS, Y QUE CUALQUIERA DE ELLOS ACTUE DEFORMANDO EL SHAPE DE TEXT ORGANIC. PIENSA QUE LUEGO QUIERO QUE SE PUEDA ANADIR MAS PUNTOS FACILMENTE. SI ES POSIBLE PODRIAS APROVECHAR PARA CREAR UNA CLASE Y SUS ARCHIVOS .H/.CPP, Y TAMBIEN PUEDES MOVER ALLI LA ACTUACION DE `MOUSE TWEAKS`. 
[ ] anade un ofParam `thickness` para el grosor de la linea outline, normalizado `float` de 0.f a 1.0f y una constnte de max 10 points de grosor en las constantes de `organicTextConstants.h`. anadelo a los `ofParameterGroup` junto a `draw outline bool`. debe aparecer en el preset tambien. ademas ahora quiero que `bool draw outline` tambien se incluya en el `preset`.
[ ] el `timing` o tiempo, o velocidad de todas las animaciones, por frame debe ser independiente del `framerate`. es decir, si el framerate baja las animaciones deben seguir a la misma `velocidad`. para ello, en vez de usar `frameCount` o similar, usa `ofGetElapsedTimef()` o `deltaTime` para calcular los tiempos de las animaciones.
[ ] quiero hacer un archivo clase nuevo para centralizar donde se guardan los puntos tanto del outline como de las animaciones, tanto de los trails como de los puntos normales. vamos a llamar a esta clase `organicTextData`. y accederemos a ella para guardar y leer los puntos centralizadamente. via un smart pointer cpp.
- En animation modes `pulse` y `wave` de organicText funcionan animando los puntos segun una funcion relativa a un punto horizontalmente centrado en el texto dibujado. me gustaria qeye pudiera modificarse el punto x desde la izquiera a la derecha, donde 0.5 sea el centro como hace ahora. tambien podemos usarlo para el modo `orbit` haciendo rotar desde otro x y no siempre desde el centro. anade otro ofparam 0-1 llamado animOriginX o similar.
- he actualizado y mejorado ofxTweenLiteHelper. puedes ver el ejemplo de uso en ofxTweenLite/example4/src. revisa e implementa estas nuevas mejoras en organicText.h/.cpp y si necesitas toca cosas en ofapp

----

## NOTES TO REMEMBER:
- lee en profundidadAI-AGENTS-GUIDE.md (AGENTS.md y RULES.md principalmente, memorizalos. son los dos archivos para Agentes mas importantes)
- hazme propuestas antes de implementar nada
- ignora los TODO incrustados en el codigo!
- revisa y modifica solo /src, principalmente src/organicText.h/cpp, y si es necesario ofApp.h/.cpp.
- no toques main.cpp.
- si necesitas (y te autorizo) ejecutar la app usa Debug ya que Release no esta bien configurado. Pero mejor ya me encargo yo de compilar y ejecutar.
- no hagas los git commits, solo proponme hacerlo yo cuando cambios grandes o haya nuevas features funcionando.

----

# IGNORE: PERSONAL MISC NOTES:
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

----

# IGNORE: PERSONAL MISC NOTES: (TO BE COPIED TO THE AGENT)
- AHORA REVISA EN PROFUNDIDAD `AI-AGENTS-GUIDE.md` (SI AUN NO LO HAS HECHO) Y PROCEDE A REALIZAR `DO NOW LIST` DEL file `docs/AI-Assistant/Status/TODO.md`. (Ignora por ahora la seccion `# DO NEXT LIST` - que haremos luego - y el resto del archivo debajo.)