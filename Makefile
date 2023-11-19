.PHONY: clean All

All:
	@echo "----------Building project:[ Calcul_Intermittent - Debug ]----------"
	@cd "Calcul_Intermittent" && "$(MAKE)" -f  "Calcul_Intermittent.mk"
clean:
	@echo "----------Cleaning project:[ Calcul_Intermittent - Debug ]----------"
	@cd "Calcul_Intermittent" && "$(MAKE)" -f  "Calcul_Intermittent.mk" clean
