## 🚀 FLUJO DE TRABAJO RECOMENDADO

   ### 1. INICIO DE SESIÓN ⭐

     "Lee /docs/AI-Assistant/PROJECT-CONTEXT.md para entender el proyecto"

   Resultado: Tengo contexto completo en 30 segundos sin explicaciones largas.

   ### 2. CHECK STATUS ACTUAL

     "Revisa /docs/AI-Assistant/CURRENT-STATE.md y /docs/TODO/Current-Tasks.md - ¿qué debería hacer ahora?"

   Resultado: Te doy prioridades claras basadas en el estado actual.

   ### 3. DESARROLLO DIRIGIDO

   #### Para tareas específicas:

     "Quiero añadir tooltips a los parámetros GUI - muéstrame cómo"
     "Necesito crear un nuevo preset número 10 - ayúdame"
     "El rendimiento está lento - diagnostica y optimiza"

   #### Para exploración:

     "Revisa el código y sugiere 3 mejoras prioritarias"
     "¿Qué funciones necesitan comentarios urgentemente?"
     "Encuentra posibles bugs o problemas de rendimiento"

   ### 4. IMPLEMENTACIÓN GUIADA

     "Implementa [tarea] siguiendo los patrones en /docs/AI-Assistant/CODE-PATTERNS.md"

   Resultado: Código consistente con las convenciones del proyecto.

   ### 5. TESTING Y VALIDACIÓN

     "Compila, testa y verifica que todos los presets 0-9 funcionen"
     "Ejecuta el checklist de /docs/AI-Assistant/QUICK-COMMANDS.md"

   ### 6. COMMIT Y DOCUMENTACIÓN

     "Haz commit de los cambios y actualiza /docs/AI-Assistant/CURRENT-STATE.md si es necesario"

   -------------------------------------------------------------------------------

   ## 💡 COMANDOS ESPECÍFICOS MÁS ÚTILES

   ### 🔥 COMANDOS FRECUENTES

   #### Inicio rápido:

     "Context: TextTypoOrganic02, lee /docs/AI-Assistant/PROJECT-CONTEXT.md y dime el estado actual"

   #### Análisis de código:

     "Revisa src/organicText.cpp y sugiere mejoras basándote en /docs/TODO/Current-Tasks.md"

   #### Desarrollo guiado:

     "Implementa [función X] siguiendo el patrón de /docs/AI-Assistant/CODE-PATTERNS.md"

   #### Debugging:

     "El preset 3 no funciona bien - diagnostica usando los patrones de debug de CODE-PATTERNS.md"

   #### Performance:

     "Analiza el rendimiento y sugiere optimizaciones basándote en CURRENT-STATE.md"

   ### 🎯 COMANDOS POR TIPO DE TAREA

   #### Nuevas características:

     "Quiero añadir [característica X] - muéstrame el plan paso a paso usando QUICK-COMMANDS.md"

   #### Bug fixing:

     "Hay un problema con [X] - revisa Known-Bugs.md y dame solución"

   #### Refactoring:

     "Mejora la función [X] manteniendo los patrones de CODE-PATTERNS.md"

   #### Testing:

     "Crea tests para [función] siguiendo las convenciones del proyecto"

   -------------------------------------------------------------------------------

   ## 🎨 COMANDOS CREATIVOS Y AVANZADOS

   ### Exploración creativa:

     "Sugiere 3 nuevos presets visuales interesantes basándote en los existentes"
     "¿Qué nuevos tipos de animación serían fáciles de implementar?"

   ### Optimización específica:

     "El connectionDistance está causando lag - optimiza esta función"
     "Los trails consumen mucha memoria - mejora la gestión"

   ### Desarrollo dirigido por objetivos:

     "Objetivo: añadir FPS counter. Planifica, implementa y testa siguiendo nuestras convenciones"

   -------------------------------------------------------------------------------

   ## ⚡ TIPS PARA MÁXIMA EFICIENCIA

   ### DO's ✅

     * Siempre empieza mencionando el archivo AI-Assistant relevante
     * Sé específico sobre qué parte del código te interesa
     * Referencia las convenciones de CODE-PATTERNS.md cuando pidas código
     * Pide testing después de cambios importantes
     * Actualiza documentación cuando hagas cambios significativos

   ### DON'Ts ❌

     * No pidas explicaciones del proyecto desde cero (usa PROJECT-CONTEXT.md)
     * No ignores las prioridades de CURRENT-STATE.md
     * No rompas las convenciones de naming establecidas
     * No olvides testar los presets después de cambios

   -------------------------------------------------------------------------------

   ## 🔄 WORKFLOW EJEMPLO COMPLETO

     Usuario: "Context: TextTypoOrganic02. Lee AI-Assistant/CURRENT-STATE.md y dime qué tarea de alta prioridad debería hacer ahora"

     Copilot: [Lee CURRENT-STATE.md] "Prioridad alta: añadir comentarios a sampleStringPoints(). Te muestro la función y sugiero comentarios..."

     Usuario: "Perfecto, implementa esos comentarios siguiendo CODE-PATTERNS.md"

     Copilot: [Implementa comentarios siguiendo convenciones]

     Usuario: "Compila y testa que todo funcione"

     Copilot: [Compila, testa presets 0-9, reporta resultados]

     Usuario: "Haz commit con mensaje apropiado"

     Copilot: [Hace git commit con mensaje descriptivo]

     Usuario: "Actualiza CURRENT-STATE.md marcando esta tarea como completada"

     Copilot: [Actualiza documentación]

   -------------------------------------------------------------------------------

   ## 🎯 RESULTADO ESPERADO

   Con este flujo conseguirás:

   ✅ Sesiones más eficientes - Sin tiempo perdido en explicaciones
   ✅ Código consistente - Siguiendo siempre las convenciones
   ✅ Desarrollo dirigido - Enfocado en prioridades reales
   ✅ Menos errores - Testing sistemático después de cambios
   ✅ Documentación actualizada - El proyecto siempre refleja el estado real