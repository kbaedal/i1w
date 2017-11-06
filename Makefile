.PHONY: clean All

All:
	@echo "----------Building project:[ in1weekend - Debug ]----------"
	@"$(MAKE)" -f  "in1weekend.mk"
clean:
	@echo "----------Cleaning project:[ in1weekend - Debug ]----------"
	@"$(MAKE)" -f  "in1weekend.mk" clean
